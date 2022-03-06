/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddi <maddi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 01:07:57 by maddi             #+#    #+#             */
/*   Updated: 2022/03/05 23:19:46 by maddi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_cmd	*ft_newlst(char **envp, char *arg)
{
	t_cmd	*new;

	if (!envp)
		return (NULL);
	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->args = ft_split(arg, ' ');
	if (new->args == NULL)
		return(ft_handle_error("split malloc in ft_newlst"));
	new->binpath = ft_get_bin_path(envp, new->args);
	if (new->binpath == NULL)
		return(ft_handle_error("ft_get_bin_path malloc in ft_newlst"));
	new->next = NULL;
	return (new);
}

void	ft_lstadd_cmd(t_cmd **first, char **envp, char *arg)
{
	t_cmd	*newcmd;
	t_cmd	*tmp;

	if (!envp || !arg)
		return ;
	newcmd = ft_newlst(envp, arg);
	if (!newcmd)
	{
		perror("ft_newlst malloc in addcmd");
		ft_putstr_fd(strerror(errno), 2);
		return ;
	}
	tmp = *first;
	while (tmp && tmp->next)
		tmp = tmp->next;
	tmp->next = newcmd;
}

int	ft_cmdsize(t_cmd *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

void	ft_exec_cmd_lst(char **envp, t_fd *fd, t_cmd *cmdlst)
{
	t_cmd	*current;

	current = cmdlst;
	if (!envp)
		return ;
	while (current)
	{
		ft_redir(envp, current, fd, cmdlst);
		current = current->next;
	}
}
