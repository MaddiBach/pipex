/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddi <maddi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 00:13:12 by maddi             #+#    #+#             */
/*   Updated: 2022/01/22 17:23:05 by maddi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
  //////////////
 /* INCLUDES */
//////////////

# include "libft/libft.h"
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# define READ 0
# define WRITE 1

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

char    **ft_get_bin_path(char **envp, char **args);   // <- Parse environment variables to return multiple binary path : **/bin
char    *ft_get_access(char **binpath);   // <- Parse multiple binary path to return path to accessible binary 
t_cmd   *ft_newlst(char **envp, char *arg, int index);
void    ft_lstadd_cmd(t_cmd **first, char **envp, char *arg, int index);
char    **ft_join_path_bin(char **binpath, char **args);
void    ft_close( int *fd);

#endif