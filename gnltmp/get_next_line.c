/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddi <maddi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 16:35:21 by maddi             #+#    #+#             */
/*   Updated: 2021/12/14 17:04:53 by maddi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	buff[FD_NBR][BUFFER_SIZE + 1];
	char		*line;
	int			readreturn;

	if (fd < 0 || fd > FD_NBR || BUFFER_SIZE <= 0)
		return (NULL);
	line = malloc(1);
	line[0] = 0;
	while (ft_get_endl(buff[fd]) == -1)
	{
		line = ft_strjoin_to_l(line, buff[fd], 0);
		if (!line)
			return (NULL);
		readreturn = read(fd, buff[fd], BUFFER_SIZE);
		buff[fd][readreturn] = 0;
		if (readreturn <= 0)
		{		
			line = ft_strjoin_to_l(line, buff[fd], 1);
			return (line);
		}
	}
	line = ft_strjoin_to_l(line, buff[fd], 0);
	ft_strlcpy(buff[fd], buff[fd] + ft_get_endl(buff[fd]) + 1, BUFFER_SIZE);
	return (line);
}
