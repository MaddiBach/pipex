/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddi <maddi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 10:26:09 by maddi             #+#    #+#             */
/*   Updated: 2022/01/21 18:59:33 by maddi            ###   ########.fr       */
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

void    ft_redir(char **envp, t_cmd *cmdlst)
{
    int tmp = dup(STDIN_FILENO);
    int pip[2];
    int pid = fork();
    if (!pid)
    {
        // RECUPERE LENTREE STANDARD POUR CHAQUE PROCESS SAUF LE PREMIER QUI PREND infile
        dup2(pip[1], STDOUT_FILENO);
        exec;

    }
    else
    {
        //DANS LE PARENT, CLOSE LE PIPE MAIS AVANT dup2(0, fd[0]) POUR RECUP CE QUI A ETE ECRIT DEDANS
        dup2(0, pip[0]);
        close(pip[1]);
        close(pip[2]);
    }
}

/*
int main(int ac, char **av, char **envp)
{
    t_cmd *cmdlst;
    int infilefd;

    cmdlst = make_cmd_lst(ac, av, envp);
    ft_printlst(cmdlst);
    int fd = dup(0);
    printf("fd = %i", fd);
    int pip[2];
    pipe(pip);
    infilefd = open(av[1] , O_RDONLY);
    dup2(infilefd, 0);
    dup2(pip[1], 1);
    close(pip[0]);
    //close(fd);
    execve(ft_get_access(cmdlst->binpath), cmdlst->args, envp);
}*/

int main(int ac, char **av, char **envp)
{

    t_cmd *cmdlst = make_cmd_lst(ac, av, envp);
    int id = fork();
    if (id == 0)
    {
        int i = 3;
        ft_redir(fd,envp, cmdlst)
        while (i < ac - 1)
        {
            ft_redir(fd);
        }

    };    
}