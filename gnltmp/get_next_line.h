/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddi <maddi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 17:03:16 by maddi             #+#    #+#             */
/*   Updated: 2021/12/14 17:34:31 by maddi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define FD_NBR 256

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

int		ft_strclen(char *str, char c);
void	ft_bzero(char *str, int n);
int		ft_get_endl(char *str);
char	*ft_strcdup(char *str, char c);
char	*ft_strjoin_to_l(char *line, char *buff, int key);
char	*get_next_line(int fd);
void	*ft_realloc(void *ptr, int size, int newsize);
int		ft_strlcpy(char *dst, char *src, int dst_size);
#endif
