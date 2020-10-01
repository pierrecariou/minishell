/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 17:42:06 by pcariou           #+#    #+#             */
/*   Updated: 2019/10/28 14:52:54 by pcariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t i;
	size_t len;
	size_t fix_len;

	i = 0;
	if (dst == 0 && src && dstsize == 0)
		return (ft_strlen(src));
	len = ft_strlen(dst);
	fix_len = ft_strlen(dst);
	while ((src[i]) && i < (dstsize - fix_len - 1) && dstsize != 0 &&
			fix_len < dstsize)
	{
		dst[len] = (src[i]);
		len++;
		i++;
	}
	if (dstsize != 0 && fix_len < dstsize)
		dst[len] = '\0';
	if (dstsize == 0)
		return ((size_t)ft_strlen(src));
	if (dstsize > fix_len)
		return ((size_t)ft_strlen(src) + fix_len);
	else
		return ((size_t)ft_strlen(src) + dstsize);
}
