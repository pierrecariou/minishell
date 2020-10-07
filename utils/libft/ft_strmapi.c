/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 14:27:15 by pcariou           #+#    #+#             */
/*   Updated: 2019/10/28 15:12:48 by pcariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*new_s;
	int				len;

	i = 0;
	len = 0;
	if (s == 0 || f == 0)
		return (0);
	while (s[len])
		len++;
	if (!(new_s = malloc(sizeof(char) * (len + 1))))
		return (0);
	while (s[i])
	{
		new_s[i] = (*f)(i, (s[i]));
		i++;
	}
	new_s[i] = '\0';
	return (new_s);
}
