/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddi <maddi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 10:26:09 by maddi             #+#    #+#             */
/*   Updated: 2022/03/06 06:45:04 by maddi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_cmd	*make_cmd_lst(int ac, char **av, char **envp, int heredoc)
{
	int		i;
	t_cmd	*lst;

	if (!heredoc)
	{
		lst = ft_newlst(envp, av[3]);
		i = 4;
	}
	else
	{
		lst = ft_newlst(envp, av[2]);
		i = 3;
	}
	while (i < ac - 1)
	{
		ft_lstadd_cmd(&lst, envp, av[i]);
		i++;
	}
	return (lst);
}

int	ft_heredoc(char *delim, t_fd *fd)
{
	char	*line;
	pid_t	pid;
	int		openret;

	openret = open("/tmp/.ft_pipexheredoc", O_CREAT| O_RDWR, 0777);
	if (openret == -1)
	{
		ft_handle_error("open in ft_heredoc");
		return (-1);
	}
	ft_read_sdin(delim, openret);
	return (openret);
}

void	ft_redir(char **envp, t_cmd *current, t_fd *fd, t_cmd *firstcmd)
{
	pid_t	pid;
	int	pipret;

	pipret = pipe(fd->pip);
	if (pipret == -1)
		ft_handle_error("pipe in ft_redir");
	pid = fork();
	if (!pid)
	{
		ft_dup(current, firstcmd, fd);
		ft_close(fd);
		execve(current->binpath, current->args, envp);
	}
	dup2(fd->pip[READ], fd->sdin);
	close(fd->pip[WRITE]);
	close(fd->pip[READ]);
}

int	main(int ac, char **av, char **envp)
{
	t_cmd	*cmdlst;
	t_fd	*fd;
	int		dupret;

	if (ac < 5 || *envp == NULL)
		return (-1);
	fd = ft_open(ac, av, ft_strncmp(av[1], "here_doc", 8));
	if (!fd)
		return (-1);
	cmdlst = make_cmd_lst(ac, av, envp, ft_strncmp(av[1], "here_doc", 8));
	dupret = dup2(fd->infile, STDIN_FILENO);
	if (dupret == -1)
	{
		perror("dup2 in main");
		return (-1);
	}
	ft_exec_cmd_lst(envp, fd, cmdlst);
	//ft_cmdclear(&cmdlst, ft_delcmd);
	waitpid(-1, NULL, -1);
	ft_close(fd);
}
