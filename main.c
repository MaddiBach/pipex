/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddi <maddi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 10:26:09 by maddi             #+#    #+#             */
/*   Updated: 2022/01/22 20:18:03 by maddi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_cmd   *make_cmd_lst(int ac, char **av, char **envp)
{
    int i;
    t_cmd *lst;

    lst = ft_newlst(envp, av[2], 2);
    i = 3;
    while (i < ac)
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
        printf("pos = %i", lst->pos);
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

void    ft_close(int *fd)
{
    dup2(fd[0], STDIN_FILENO);
    close(fd[1]);
    close(fd[0]);
}

pid_t    ft_redir(char **envp, t_cmd *cmdlst, int sdin)
{
    int pip[2];
    pipe(pip);
    int pid = fork();
    if (!pid)
    {
        close(pip[READ]);
        dup2(pip[WRITE], STDOUT_FILENO);
        close(pip[WRITE]);
        execve(ft_get_access(cmdlst->binpath), cmdlst->args, envp);
    }
    close(pip[WRITE]);
    dup2(pip[READ], sdin);
    close(pip[READ]);
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

int main(int ac, char **av, char **envp)
{

    t_cmd *cmdlst = make_cmd_lst(ac, av, envp);
    int processes[ft_cmdsize(cmdlst) + 1];
    int sdin = dup(STDIN_FILENO);
    if (!cmdlst)
        return (1);
    int i = 0;
    int fopen = open(av[1], O_RDONLY);
    dup2(fopen, STDIN_FILENO);
    while (cmdlst->next)
    {
        processes[i++] = ft_redir(envp, cmdlst, sdin);
        cmdlst = cmdlst->next;
    }
    int dope = open(av[ac - 1],O_CREAT | O_TRUNC | O_RDWR, 0777);
    printf("file = %s\n", av[ac - 1]);
    if (dope < 0)
        puts("error");
    dup2(dope, STDOUT_FILENO);
    execve(ft_get_access(cmdlst->binpath), cmdlst->args, envp);
    i =  0;
    while(i <= ft_cmdsize(cmdlst))
        waitpid(processes[i++], NULL, 0);
    close(fopen);
    close(dope);
    close(sdin);
}