/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 17:15:52 by pcariou           #+#    #+#             */
/*   Updated: 2019/10/28 16:14:17 by pcariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strncopy(char *dest, const char *src, unsigned int n)
{
	unsigned int i;

	i = 0;
	while (src[i] && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

size_t			ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	if (dst == 0 || src == 0)
		return (0);
	if (dstsize > 0)
		ft_strncopy(dst, src, dstsize - 1);
	if (ft_strlen(src) >= dstsize)
		return (ft_strlen(src));
	return (ft_strlen(dst));
}
