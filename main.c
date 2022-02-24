/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddi <maddi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 10:26:09 by maddi             #+#    #+#             */
/*   Updated: 2022/02/24 14:06:43 by maddi            ###   ########.fr       */
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

void	ft_heredoc(char *delim, t_fd *fd)
{
	char	*line;
	pid_t	pid;
	int		pipret;

	pipret = pipe(fd->pip);
	if (pipret == -1)
	{
		perror("pipe ");
		ft_putstr_fd(strerror(errno), 2);
		return ;
	}
	pid = fork();
	if (pid == 0)
	{
		delim = ft_strjoin(delim, "\n"); //can fail
		if (!delim)
		{
			perror("malloc in heredoc");
			ft_putstr_fd(strerror(errno), 2);
			exit(EXIT_FAILURE);
		}
		line = get_next_line(fd->sdin);
		while (line)
		{
			if (!ft_strncmp(line, delim, ft_strlen(delim)))
				ft_close_heredoc(fd, line, delim);
			ft_putstr_fd(line, fd->pip[WRITE]);
			free(line);
			line = get_next_line(fd->sdin);
		}
		free(line);
		free(delim);
	}
	else
	{
		dup2(fd->pip[READ], fd->sdin);
		waitpid(pid, NULL, 0);
		close(fd->pip[0]);
		close(fd->pip[1]);
	}
}

void	ft_redir(char **envp, t_cmd *current, t_fd *fd, t_cmd *firstcmd)
{
	int	pid;

	pipe(fd->pip);
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

	if (ac < 5)
		return (-1);
	fd = ft_open(ac, av, ft_strncmp(av[1], "here_doc", 8));
	if (!fd)
		return (-1);
	cmdlst = make_cmd_lst(ac, av, envp, ft_strncmp(av[1], "here_doc", 8));
	dupret = dup2(fd->infile, STDIN_FILENO);
	if (dupret == -1)
	{
		perror("dup2 ");
		ft_putstr_fd(strerror(errno), 2);
		return (-1);
	}
	if (!ft_strncmp(av[1], "here_doc", 8))
		ft_heredoc(av[2], fd);
	ft_cmditer(envp, fd, cmdlst);
	//ft_cmdclear(&cmdlst, ft_delcmd);
	waitpid(-1, NULL, -1);
	ft_close(fd);
}
