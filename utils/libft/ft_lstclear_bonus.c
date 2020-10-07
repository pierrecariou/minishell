/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 17:54:09 by pcariou           #+#    #+#             */
/*   Updated: 2019/10/21 15:32:55 by pcariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list *elem;
	t_list *tmp;

	if (!lst || !del)
		return ;
	elem = *lst;
	tmp = elem;
	while (elem)
	{
		tmp = tmp->next;
		ft_lstdelone(elem, del);
		elem = tmp;
	}
	*lst = 0;
}
