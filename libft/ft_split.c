/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 19:38:23 by maddi             #+#    #+#             */
/*   Updated: 2021/12/01 19:53:04 by maddi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nb_words_in_str(char *str, char c)
{
	int		i;
	int		nbwords;

	nbwords = 0;
	i = 0;
	if (i == 0 && str[i] != c)
		nbwords++;
	while (str[i] && str[i + 1])
	{
		if (str[i] == c && i != 0 && str[i + 1] != 0 && str[i + 1] != c)
			nbwords++;
		i++;
	}
	return (nbwords);
}

static char	*ft_strndup(char *str, int n)
{
	char	*newstr;

	newstr = malloc(sizeof(char) * (n + 1));
	if (newstr == NULL)
		return (NULL);
	ft_memcpy(newstr, str, n * sizeof(char));
	newstr[n] = 0;
	return (newstr);
}

static int	ft_wordlen(char *str, char c)
{
	int	len;

	len = 0;
	while (str[len] && str[len] != c)
		len++;
	return (len);
}

static void	*ft_free_tab(char **tab, int nbline)
{
	while (nbline >= 0)
	{
		free(tab[nbline]);
		nbline--;
	}
	free(tab);
	return (NULL);
}

char	**ft_split(const char *s, char c)
{
	char	**tab;
	int		nbline;

	nbline = 0;
	if (s == NULL)
		return (NULL);
	tab = malloc(sizeof(char *) * (ft_nb_words_in_str((char *)s, c) + 1));
	if (tab == NULL)
		return (NULL);
	while (*s)
	{
		while (*s == c)
			s++;
		if (ft_wordlen((char *)s, c))
		{
			tab[nbline] = ft_strndup((char *)s, ft_wordlen((char *)s, c));
			if (tab[nbline] == NULL)
				return (ft_free_tab(tab, nbline));
			s += ft_wordlen((char *)s, c);
			nbline++;
		}
	}
	tab[nbline] = NULL;
	return (tab);
}
