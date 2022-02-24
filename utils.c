/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddi <maddi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 04:07:39 by maddi             #+#    #+#             */
/*   Updated: 2022/02/24 12:49:13 by maddi            ###   ########.fr       */
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

void	ft_close_heredoc(t_fd *fd, char *line, char *delim)
{
	ft_close(fd);
	free(line);
	free(delim);
	exit(EXIT_SUCCESS);
}

t_fd	*ft_open(int ac, char **av, int heredoc)
{
	t_fd	*fd;

	fd = malloc(sizeof(t_fd));
	if (!fd)
		return (NULL);
	if (!heredoc)
	{
		fd->outfile = open(av[ac - 1], O_CREAT | O_APPEND | O_RDWR, 0777);
		fd->infile = 0;
	}
	else
	{
		fd->infile = open(av[1], O_RDONLY);
		fd->outfile = open(av[ac - 1], O_CREAT | O_TRUNC | O_RDWR, 0777);
	}
	if (fd->infile < 0)
	{
		perror("infile open :");
		ft_putstr_fd(strerror(errno), 2);
		return (NULL);
	}
	if (fd->outfile < 0)
	{
		perror("outfile open :");
		ft_putstr_fd(strerror(errno), 2);
		return (NULL);
	}
	fd->sdin = dup(STDIN_FILENO);
	return (fd);
}

void	*ft_handle_error(char *error)
{
	perror(error);
    return (NULL);
}

void	ft_dup(t_cmd *current, t_cmd *firstcmd, t_fd *fd)
{
    int dupret;

	if (current == firstcmd)
    {
		dupret = dup2(fd->sdin, STDIN_FILENO);
        if (dupret == -1)
        {
            ft_handle_error("dup2 firstcmd");
            return ;
        }
    }
	if (current->next)
    {
		dupret = dup2(fd->pip[WRITE], STDOUT_FILENO);
        if (dupret == -1)
        {
            ft_handle_error("dup2 cmd");
            return ;
        }
    }
	else
    {
		dupret = dup2(fd->outfile, STDOUT_FILENO);
        if (dupret == -1)
        {
            ft_handle_error("dup2 lastcmd");
            return ;
        }
    }
}