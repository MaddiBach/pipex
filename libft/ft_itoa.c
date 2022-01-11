/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddi <maddi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 19:43:30 by maddi             #+#    #+#             */
/*   Updated: 2021/12/07 02:01:15 by maddi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	nbr_len(long n)
{
	int		len;

	len = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

static char	*str_fill(long n, char *str, int sign)
{
	if (n == 0)
	{
		*str = '0';
		*++str = 0;
		return (str);
	}
	if (sign == 1)
	{
		*str = '-';
		str++;
	}
	*(str + nbr_len(n)) = '\0';
	str += nbr_len(n) - 1;
	while (n > 0)
	{
		*str = (n % 10) + 48;
		n = n / 10;
		str--;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	int				sign;
	unsigned int	nbr;
	char			*str;

	sign = 0;
	nbr = n;
	if (n < 0)
	{
		sign = 1;
		nbr = -n;
	}
	str = malloc(sizeof(char) * nbr_len(nbr) + 1 + sign);
	if (str == 0)
		return (NULL);
	str_fill(nbr, str, sign);
	return (str);
}
