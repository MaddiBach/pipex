/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddi <maddi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 00:15:45 by maddi             #+#    #+#             */
/*   Updated: 2021/12/05 15:22:37 by maddi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_in_charset(char c, char const *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

static int	ft_get_trim_start(char const *str, char const *set)
{
	int	i;

	i = 0;
	while (str[i] && ft_in_charset(str[i], set))
		i++;
	return (i);
}

static int	ft_get_trim_end(char const *str, char const *set)
{
	int	i;

	i = ft_strlen(str) - 1;
	while (i && ft_in_charset(str[i], set))
		i--;
	return (i);
}

char	*ft_strtrim(char const *str, char const *set)
{
	int		trimstart;
	int		trimend;
	char	*trim;

	if (!str)
		return (NULL);
	if (!set)
	{
		trim = ft_strdup(str);
		return (trim);
	}
	trimstart = ft_get_trim_start(str, set);
	trimend = ft_get_trim_end(str, set) - trimstart;
	trim = ft_substr(str, trimstart, trimend + 1);
	return (trim);
}
