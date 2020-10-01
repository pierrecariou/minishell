/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 15:19:41 by pcariou           #+#    #+#             */
/*   Updated: 2019/10/28 16:13:06 by pcariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t i;
	size_t a;

	i = 0;
	a = 0;
	if (!(needle[0]))
		return ((char *)haystack);
	while (i < len && haystack[i])
	{
		while (haystack[i + a] == needle[a] && (i + a) < len)
		{
			if (needle[a + 1] == '\0')
				return (&(((char *)haystack)[i]));
			a++;
		}
		a = 0;
		i++;
	}
	return (0);
}
