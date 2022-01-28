/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddi <maddi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 04:07:39 by maddi             #+#    #+#             */
/*   Updated: 2022/01/28 05:16:37 by maddi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_close(t_fd *fd)
{
	close(fd->pip[0]);
	close(fd->pip[1]);
	close(fd->sdin);
	close(fd->outfile);
    close(fd->infile);
}

t_fd    *ft_open(int ac, char **av)
{
    t_fd    *fd;

    fd = malloc(sizeof(t_fd));
    if (!fd)
        return (NULL);
    fd->outfile = open(av[ac - 1],O_CREAT | O_TRUNC | O_RDWR, 0777);
    if (fd->outfile < 0)
        return (NULL);
    fd->infile = open(av[1], O_RDONLY);
    if (fd->infile < 0)
        return (NULL);
    fd->sdin = dup(STDIN_FILENO);
    return (fd);    
}