/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddi <maddi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 00:33:08 by maddi             #+#    #+#             */
/*   Updated: 2022/03/30 02:22:37 by maddi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_cmd
{
        char                    *binpath;
        char                    **args;
}                                       t_cmd;


typedef enum rdwr 
{
    READ,
    WRITE
}  rdwr;

void    ft_freesplit(char **str);
void    ft_delcmd(t_cmd *cmd);
char	*ft_get_bin_path(char **envp, char **args);
char	*ft_get_absolute_path(char **envp, char **args);
char	*ft_get_access(char **binpath);
char	**ft_join_path_bin(char **binpath, char **args);

#endif