/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 16:35:23 by maddi             #+#    #+#             */
/*   Updated: 2021/11/29 14:15:49 by maddi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*start;
	char	chr;

	chr = (char)c;
	start = (char *)s;
	if (chr == '\0')
		return (start + ft_strlen((char *)s));
	while (*s)
	{
		s++;
	}
	while (s != start - 1)
	{
		if (chr == *s)
			return ((char *)s);
		s--;
	}
	return (NULL);
}
