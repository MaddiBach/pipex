/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddi <maddi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 00:13:12 by maddi             #+#    #+#             */
/*   Updated: 2022/01/28 23:12:54 by maddi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
  //////////////
 /* INCLUDES */
//////////////

# include "libft/libft.h"
# include "get_next_line/get_next_line.h"
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
    pid_t           pid;
    struct  s_cmd   *next;
}                   t_cmd;

typedef struct s_fd
{
	int pip[2];
	int sdin;
	int outfile;
  int infile;
}				t_fd;

  /////////////
 /* PARSING */
/////////////

char    **ft_get_bin_path(char **envp, char **args);   // <- Parse environment variables to return multiple binary path : **/bin
char    *ft_get_access(char **binpath);   // <- Parse multiple binary path to return path to accessible binary 
t_cmd   *ft_newlst(char **envp, char *arg);   // <- create a new list 
void    ft_lstadd_cmd(t_cmd **first, char **envp, char *arg);   // <- add a command to the end of the list
char    **ft_join_path_bin(char **binpath, char **args);   // <- joins the PATH with the command name
void    ft_close(t_fd *fd);   // <- close all files stored in struct
t_fd    *ft_open(int ac, char **av,int heredoc);   // <- open all files needed and store them in a struc
#endif