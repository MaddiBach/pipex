/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddi <maddi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 04:50:14 by maddi             #+#    #+#             */
/*   Updated: 2022/03/31 09:56:34 by maddi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void    ft_freesplit(char **str)
{
    int i;

    i = 0;
    if (!str)
        return ;
    while (str[i])
    {
        free(str[i]);
        i++;
    }
    free(str);
}

void    ft_delcmd(t_cmd *cmd)
{
    free(cmd->binpath);
    ft_freesplit(cmd->args);
    free(cmd);
}

void	ft_cmdclear(t_cmd **cmd, void (*del)(t_cmd *))
{
	t_cmd	*temp;

	if (!cmd || !*cmd || !del)
		return ;
	while (*cmd)
	{
		temp = (*cmd)->next;
		del(*cmd);
		*cmd = temp;
	}
}