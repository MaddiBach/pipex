/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddi <maddi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 17:48:22 by maddi             #+#    #+#             */
/*   Updated: 2021/12/05 14:43:55 by maddi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	if (!*little)
		return ((char *)big);
	if (len == 0)
		return (NULL);
	while (len && *big)
	{
		if (ft_strlen(little) > len)
			return (NULL);
		if (!ft_strncmp(big, little, ft_strlen(little)))
			return ((char *)big);
		big++;
		len--;
	}
	return (NULL);
}
