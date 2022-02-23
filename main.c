/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddi <maddi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 10:26:09 by maddi             #+#    #+#             */
/*   Updated: 2022/02/16 17:42:41 by maddi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_cmd   *make_cmd_lst(int ac, char **av, char **envp, int heredoc)
{
    int i;
    t_cmd *lst;

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

void    ft_printstrs(char **strs)
{
    int i = 0;

    while (strs[i])
    {
        write(1, strs[i], ft_strlen(strs[i]));
        write(1, "\n", 1);
        i++;
    }
}

void    ft_printlst(t_cmd *lst)
{
    while (lst->next)
    {
        puts("PATH : ");
        ft_printstrs(lst->binpath);
        puts("");
        puts("CMD :");
        ft_printstrs(lst->args);
        puts("");
        lst = lst->next;
    }
}

void    ft_heredoc(char *delim, t_fd *fd)
{
    char    *line;

    close (fd->pip[READ]);
    delim = ft_strjoin(delim, "\n");
    line = get_next_line(fd->sdin);
    while(line)
    {
        if (!ft_strncmp(line, delim, ft_strlen(delim)))
        {
            close(fd->pip[WRITE]);
            free(line);
            free(delim);
            exit(EXIT_SUCCESS);
        }
        ft_putstr_fd(line, fd->pip[WRITE]);
        free(line);
        line = get_next_line(fd->sdin);
    }
    //close(fd->pip[WRITE]);
    free(line);
    free(delim);
}

void    ft_redir(char **envp, t_cmd *current, t_fd *fd, t_cmd *firstcmd)
{
    current->pid = fork();
    if (!current->pid)
    {
		if (current != firstcmd)
			dup2(fd->sdin, STDIN_FILENO);
		if (current->next)
        	dup2(fd->pip[WRITE], STDOUT_FILENO);
		else
			dup2(fd->outfile, STDOUT_FILENO);
        ft_close(fd);
        execve(ft_get_access(current->binpath), current->args, envp);
    }

    dup2(fd->pip[READ], fd->sdin);
    close(fd->pip[WRITE]);
    close(fd->pip[READ]);
}

int	ft_cmdsize(t_cmd *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}


int main(int ac, char **av, char **envp)
{
    t_cmd   *cmdlst;
    t_cmd   *current;
	t_fd        *fd;

    if (ac < 5)
        return (-1);
    fd = ft_open(ac, av, ft_strncmp(av[1], "here_doc", 8));
    if (!fd)
        return (-1);
    cmdlst = make_cmd_lst(ac, av, envp, ft_strncmp(av[1], "here_doc", 8));
    dup2(fd->infile, STDIN_FILENO);
    if (!ft_strncmp(av[1], "here_doc", 8))
        ft_heredoc(av[2], fd);
    current = cmdlst;
    while (current->next)
    {
    	pipe(fd->pip);
        ft_redir(envp, current, fd, cmdlst);
        current = current->next;
    }
	ft_redir(envp, current, fd, cmdlst);
    current = cmdlst;
    waitpid(-1, NULL, -1);
	ft_close(fd);
}