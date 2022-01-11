/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddi <maddi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 01:07:57 by maddi             #+#    #+#             */
/*   Updated: 2022/01/11 02:38:20 by maddi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include    "pipex.h"

t_cmd   *ft_makelst(char **envp, char **av)
{
    t_cmd   *new;

    new = malloc(sizeof(t_cmd));
    if (!new)
        return (NULL);
    new->args = ft_get_args("ls -la -l -rf");
    new->binpath = ft_get_bin_path(envp);
    new->pos = 100;
    new->next = NULL;
    return (new);
}

