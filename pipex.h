/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddi <maddi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 00:13:12 by maddi             #+#    #+#             */
/*   Updated: 2022/03/06 12:45:46 by maddi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
//////////////
/* INCLUDES */
//////////////
# define __O_TMPFILE 020000000
# define O_TMPFILE (__O_TMPFILE | O_DIRECTORY)
# define O_TMPFILE_MASK (__O_TMPFILE | O_DIRECTORY | O_CREAT)
# include "get_next_line/get_next_line.h"
# include "libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>

////////////////
/* STRUCTURES */
////////////////

typedef enum readwrite
{
	READ,
	WRITE
}					readwrite;

typedef struct s_cmd
{
	char			*binpath;
	char			**args;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_fd
{
	int				pip[2];
	int				sdin;
	int				outfile;
	int				infile;
}					t_fd;

/////////////
/* PARSING */
/////////////

char				*ft_get_absolute_path(char **envp, char **args);
char				*ft_get_bin_path(char **envp, char **args);
// <- Parse environment variables to return multiple binary path : **/bin
char				*ft_get_access(char **binpath);
// <- Parse multiple binary path to return path to accessible binary
t_cmd				*ft_newlst(char **envp, char *arg);
// <- create a new list
void				ft_lstadd_cmd(t_cmd **first, char **envp, char *arg);
// <- add a command to the end of the list
char				**ft_join_path_bin(char **binpath, char **args);
// <- joins the PATH with the command name
void				ft_close(t_fd *fd);
// <- close all files stored in struct
t_fd				*ft_open(int ac, char **av, int heredoc);
// <- open all files needed and store them in a struc
void				ft_close_heredoc(t_fd *fd, char *line, char *delim);
// <- close needed fd + free line + free delim when finished reading here_doc
void				ft_redir(char **envp, t_cmd *current, t_fd *fd,
					t_cmd *firstcmd);
// <- redirect using dup2, and execute bin
void				ft_freesplit(char **str);
// <- free a splitted str
void				ft_delcmd(t_cmd *cmd);
// <- free a cmd node and its contents
void				ft_cmdclear(t_cmd **cmd, void (*del)(t_cmd *));
// <- free a list of cmds using ft_delcmd
void				ft_exec_cmd_lst(char **envp, t_fd *fd, t_cmd *cmdlst);
// <- iterate through cmd list and redir + exec
void				*ft_dup(t_cmd *cmd, t_cmd *firstcmd, t_fd *fd);
// <- redirect using dup2, with infile when positionned at firstcmd, pipe,
//	and outfile when positionned at lastcmd
void	*ft_handle_error(char *str);
void	ft_read_sdin(char *delim, int fd);
int	ft_heredoc(char *delim, t_fd *fd);


#endif