/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddi <maddi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 01:07:57 by maddi             #+#    #+#             */
/*   Updated: 2022/01/21 10:55:23 by maddi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include    "pipex.h"

t_cmd   *ft_newlst(char **envp, char *arg, int index)
{
    t_cmd   *new;

    new = malloc(sizeof(t_cmd));
    if (!new)
        return (NULL);
    new->args = ft_split(arg, ' ');
    new->binpath = ft_get_bin_path(envp, new->args);
    new->pos = index - 2;
    new->next = NULL;
    return (new);
}

void    ft_lstadd_cmd(t_cmd **first, char **envp, char *arg, int index)
{
    t_cmd   *newcmd;
    t_cmd   *tmp;

    if (!envp || !arg)
        return ;
    newcmd = ft_newlst(envp, arg, index);
    tmp = *first;
    while (tmp && tmp->next)
        tmp = tmp->next;
    tmp->next = newcmd;
}
/*
void    ft_lstiter(t_cmd *first, void (*f)(void *))
{
    if (!first)
        return ;
    while (first)
    {
        f(first);
        first = first->next;
    }
}*/

