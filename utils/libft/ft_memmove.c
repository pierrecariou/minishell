/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 10:43:08 by pcariou           #+#    #+#             */
/*   Updated: 2019/10/28 14:43:44 by pcariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char *new_dst;
	char *new_src;

	if (dst == 0 && src == 0)
		return (0);
	new_src = (char *)src;
	new_dst = (char *)dst;
	if (new_src < new_dst)
	{
		while (len > 0)
		{
			new_dst[len - 1] = new_src[len - 1];
			len--;
		}
		return (dst);
	}
	else
		ft_memcpy(dst, src, len);
	return (dst);
}
