/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 09:33:18 by pcariou           #+#    #+#             */
/*   Updated: 2019/10/22 18:27:58 by pcariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*new_dest;

	i = 0;
	if (dst == 0 && src == 0)
		return (0);
	new_dest = (char *)(dst);
	while (i < n)
	{
		new_dest[i] = ((char *)src)[i];
		i++;
	}
	return (dst);
}
