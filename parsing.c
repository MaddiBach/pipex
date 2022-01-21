/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddi <maddi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 00:09:38 by maddi             #+#    #+#             */
/*   Updated: 2022/01/21 11:37:55 by maddi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include    "pipex.h"

char    **ft_get_bin_path(char  **envp, char **args)
{
    int i;
    char    *trimmed;
    char    **binpath;
    char    **tmp;

    i = 0;
    while (!ft_strnstr(envp[i], "PATH", 5))
        i++;
    trimmed = ft_strtrim(envp[i], "PATH=");
    binpath = ft_split(trimmed, ':');
    free(trimmed);
    tmp = binpath;
    binpath = ft_join_path_bin(binpath, args);
   // free(tmp);

    return (binpath);
}

char    *ft_get_access(char **binpath)
{
    int     i;

    i = 0;
    while (access(binpath[i], X_OK) != 0 && binpath[i])
        i++;
    return (binpath[i]);
}

char    **ft_join_path_bin(char **binpath, char **args)
{
    int i;
    char    *tmp;

    i = 0;
    while (binpath[i])
    {
        tmp = binpath[i];
        binpath[i] = ft_strjoin(binpath[i], "/");
       // free(tmp);
        tmp = binpath[i];
        binpath[i] = ft_strjoin(binpath[i], args[0]);
       // free(tmp);
        i++;
    }
    return (binpath);
}
