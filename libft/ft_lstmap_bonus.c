/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 17:58:15 by pcariou           #+#    #+#             */
/*   Updated: 2019/10/21 15:33:33 by pcariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list *elem;
	t_list *elemcpy;

	if (!(elem = ft_lstnew((*f)(lst->content))))
	{
		ft_lstclear(&elemcpy, del);
		return (0);
	}
	lst = lst->next;
	elemcpy = elem;
	while (lst)
	{
		if (!(elem->next = ft_lstnew((*f)(lst->content))))
		{
			ft_lstclear(&elemcpy, del);
			return (0);
		}
		elem = elem->next;
		lst = lst->next;
	}
	return (elemcpy);
}
