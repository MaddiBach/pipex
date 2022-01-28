/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddi <maddi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 10:26:09 by maddi             #+#    #+#             */
/*   Updated: 2022/01/28 08:49:36 by maddi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_cmd   *make_cmd_lst(int ac, char **av, char **envp)
{
    int i;
    t_cmd *lst;

    lst = ft_newlst(envp, av[2], 2);
    i = 3;
    while (i < ac - 1)
    {
        ft_lstadd_cmd(&lst, envp, av[i], i);
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

void    ft_exec_lst(t_cmd *lst)
{
//    t_cmd *tmp;

    int pid = fork();
    if (pid == 0)
    {
        while (lst)
        {
            int pid = fork();
            lst = lst->next;
        }
    }
}

void    ft_redir(char **envp, t_cmd *current, t_fd *fd, t_cmd *firstcmd)
{
    current->pid = fork();
    if (!current->pid)
    {
		if (current == firstcmd)
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
    t_cmd *cmdlst;
    t_cmd *current;
	t_fd	*fd;

    if (ac < 5)
        return (-1);
    cmdlst = make_cmd_lst(ac, av, envp);
    fd = ft_open(ac, av);
    if (!fd)
        return (-1);
    dup2(fd->infile, STDIN_FILENO);
    current = cmdlst;
    while (current->next)
    {
    	pipe(fd->pip);
        ft_redir(envp, current, fd, cmdlst);
        current = current->next;
    }
	ft_redir(envp, current, fd, cmdlst);
    current = cmdlst;
    while(current)
    {
        waitpid(current->pid, NULL, 0);
        current = current->next;
    }
	ft_close(fd);
}