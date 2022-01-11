/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddi <maddi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 00:13:12 by maddi             #+#    #+#             */
/*   Updated: 2022/01/11 01:26:59 by maddi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
#endif
  //////////////
 /* INCLUDES */
//////////////

#include "libft.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

  ////////////////
 /* STRUCTURES */
////////////////


typedef struct s_cmd
{
    char            **binpath;
    char            **args;
    int             pos;
    struct  s_cmd   *next;
}                   t_cmd;
  /////////////
 /* PARSING */
/////////////

char    **ft_get_bin_path(char **envp);   // <- Parse environment variables to return multiple binary path : **/bin
char    *ft_get_access(char **binpath);   // <- Parse multiple binary path to return path to accessible binary 