/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddi <maddi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 04:07:39 by maddi             #+#    #+#             */
/*   Updated: 2022/02/26 17:41:16 by maddi            ###   ########.fr       */
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

void	ft_read_sdin(char *delim, t_fd *fd)
{
	char *line;
	
	line = get_next_line(STDIN_FILENO);
	while (line)
	{
		if (!ft_strncmp(line, delim, ft_strlen(delim)))
			ft_close_heredoc(fd, line, delim);
		ft_putstr_fd(line, fd->pip[WRITE]);
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	free(line);
	free(delim);
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
		return (ft_handle_error("infile open :"));
	if (fd->outfile < 0)
		return (ft_handle_error("outfile open :"));
	fd->sdin = dup(STDIN_FILENO);
	return (fd);
}

void	*ft_handle_error(char *error)
{
	perror(error);
    return (NULL);
}

void	*ft_dup(t_cmd *current, t_cmd *firstcmd, t_fd *fd)
{
    int dupret;

	if (current != firstcmd)
    {
		dupret = dup2(fd->sdin, STDIN_FILENO);
        if (dupret == -1)
            return(ft_handle_error("dup2 firstcmd"));
    }
	if (current->next)
    {
		dupret = dup2(fd->pip[WRITE], STDOUT_FILENO);
        if (dupret == -1)
            return(ft_handle_error("dup2 firstcmd"));
    }
	else
    {
		dupret = dup2(fd->outfile, STDOUT_FILENO);
        if (dupret == -1)
            return(ft_handle_error("dup2 firstcmd"));
    }
}
