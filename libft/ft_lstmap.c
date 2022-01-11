/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maddi <maddi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 14:34:13 by maddi             #+#    #+#             */
/*   Updated: 2021/12/05 14:36:18 by maddi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void(*del)(void *))
{
	t_list	*newlst;

	if (!lst || !f)
		return (NULL);
	newlst = NULL;
	while (lst->next)
	{
		ft_lstadd_back(&newlst, ft_lstnew(f(lst->content)));
		if (!ft_lstlast(newlst))
		{
			ft_lstclear(&newlst, del);
			return (NULL);
		}
		lst = lst->next;
	}
	if (lst)
		ft_lstadd_back(&newlst, ft_lstnew(f(lst->content)));
	return (newlst);
}
