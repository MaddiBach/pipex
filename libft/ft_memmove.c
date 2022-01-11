/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnelson <lnelson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 19:25:52 by maddi             #+#    #+#             */
/*   Updated: 2021/12/03 15:58:19 by lnelson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*destination;
	char	*source;
	size_t	i;

	i = 0;
	source = (char *)src;
	destination = (char *)dst;
	if (source < destination && source + len > destination)
	{
		i = len;
		while (i--)
			destination[i] = source[i];
		return (destination);
	}
	ft_memcpy(dst, src, len);
	return (destination);
}
