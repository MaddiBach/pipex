/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddi <maddi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 00:09:38 by maddi             #+#    #+#             */
/*   Updated: 2022/03/16 17:21:48 by maddi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_get_bin_path(char **envp, char **args)
{
	if (!ft_strncmp(".", args[0], 1))
		return (ft_strdup(args[0]));
	else
		return (ft_get_absolute_path(envp, args));
}

char	*ft_get_absolute_path(char **envp, char **args)
{
	int		i;
	char	**binpath;
	char	*ret;

	i = 0;
	if (!envp || !args)
		return (NULL);
	while (ft_strncmp(envp[i], "PATH=", 5))
		i++;
	binpath = ft_split(envp[i] + 6, ':');
	ft_join_path_bin(binpath, args);
	if (ft_get_access(binpath))
		ret = ft_strdup(ft_get_access(binpath));
	else
		ret = malloc(1);
	ft_freesplit(binpath);
	return (ret);
}

char	*ft_get_access(char **binpath)
{
	int	i;

	i = 0;
	while (access(binpath[i], X_OK) != 0 && binpath[i])
		i++;
	return (binpath[i]);
}

char	**ft_join_path_bin(char **binpath, char **args)
{
	int		i;
	char	*tmp;
	
	i = 0;
	if (!binpath)
		return (NULL);
	while (binpath[i])
	{
		tmp = binpath[i];
		binpath[i] = ft_strjoin(binpath[i], "/");
		free(tmp);
		tmp = binpath[i];
		binpath[i] = ft_strjoin(binpath[i], args[0]);
		free(tmp);
		i++;
	}
	return (binpath);
}
