/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 17:40:44 by pcariou           #+#    #+#             */
/*   Updated: 2019/10/21 15:32:15 by pcariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list *elem;

	if (!new)
		return ;
	if (!alst || !*alst)
	{
		*alst = new;
		return ;
	}
	elem = *alst;
	while (elem->next)
		elem = elem->next;
	elem->next = new;
	new->next = 0;
}
