/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddi <maddi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 01:17:07 by maddi             #+#    #+#             */
/*   Updated: 2021/12/05 15:19:41 by maddi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strndup(char const *str, int n)
{
	char	*newstr;

	newstr = malloc(sizeof(char) * (n + 1));
	if (newstr == NULL)
		return (NULL);
	ft_memcpy(newstr, str, n * sizeof(char));
	newstr[n] = 0;
	return (newstr);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	if (!s)
		return (NULL);
	if (len > ft_strlen((char *)s))
		len = ft_strlen((char *)(s));
	if (start >= ft_strlen(s))
	{
		return (ft_strdup(""));
	}
	s += start;
	return (ft_strndup(s, len));
}
