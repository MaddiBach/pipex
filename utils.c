/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddi <maddi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 04:07:39 by maddi             #+#    #+#             */
/*   Updated: 2022/03/09 17:10:00 by maddi            ###   ########.fr       */
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
	free(fd);
}

void	ft_read_sdin(char *delim, int fd)
{
	char *line;
	char *tmp;

	line = get_next_line(STDIN_FILENO);
	tmp = ft_strjoin(delim, "\n");
	while (line)
	{
		if (!ft_strncmp(line, tmp, ft_strlen(line)))
		{
			free(line);
			free(tmp);
			return ;
		}
		ft_putstr_fd(line, fd);
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
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
		fd->infile = ft_heredoc(av[2], fd);
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
            return(ft_handle_error("dup2 stdin -> dup(sdin) in ft_dup"));
    }
	if (current->next)
    {
		dupret = dup2(fd->pip[WRITE], STDOUT_FILENO);
        if (dupret == -1)
            return(ft_handle_error("dup2 stdout -> pipe write end in ft_dup"));
    }
	else
    {
		dupret = dup2(fd->outfile, STDOUT_FILENO);
        if (dupret == -1)
            return(ft_handle_error("dup2 stdout -> outfile in ft_dup"));
    }
	return(dupret);
}
