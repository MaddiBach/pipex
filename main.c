/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnelson <lnelson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 10:26:09 by maddi             #+#    #+#             */
/*   Updated: 2022/01/27 08:09:39 by lnelson          ###   ########.fr       */
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

pid_t    ft_redir(char **envp, t_cmd *cmdlst, t_fd *fd, int i)
{
    int pid = fork();
    if (!pid)
    {
        close(fd->pip[READ]);
		if (i != 0)
			dup2(fd->sdin, STDIN_FILENO);
		if (cmdlst->next)
        	dup2(fd->pip[WRITE], STDOUT_FILENO);
		else
		{
			puts("yay");
			dup2(fd->sdout, STDOUT_FILENO);
		}
   //     close(fd->pip[WRITE]);
        execve(ft_get_access(cmdlst->binpath), cmdlst->args, envp);
    }
    close(fd->pip[WRITE]);
    dup2(fd->pip[READ], fd->sdin);
    close(fd->pip[READ]);
    return (pid);
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

void	ft_close(t_fd *fd)
{
	close(fd->pip[0]);
	close(fd->pip[1]);
	close(fd->sdin);
	close(fd->sdout);
}

int main(int ac, char **av, char **envp)
{

    t_cmd *cmdlst = make_cmd_lst(ac, av, envp);
	t_fd	*fd;
	int i;
    int processes[ft_cmdsize(cmdlst) + 1];
	
	i = 0;
	fd = malloc(sizeof(t_fd));
    fd->sdout = open(av[ac - 1],O_CREAT | O_TRUNC | O_RDWR, 0777);
    fd->sdin = dup(STDIN_FILENO);
	pipe(fd->pip);
    int fopen = open(av[1], O_RDONLY);
    dup2(fopen, STDIN_FILENO);
    while (cmdlst->next)
    {
        processes[i] = ft_redir(envp, cmdlst, fd, i);
        cmdlst = cmdlst->next;
		i++;
    }
	ft_redir(envp, cmdlst, fd, i);
    i =  0;
    while(i <= ft_cmdsize(cmdlst))
        waitpid(processes[i++], NULL, 0);
    close(fopen);
	ft_close(fd);
} 