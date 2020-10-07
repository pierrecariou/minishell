/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 16:52:11 by pcariou           #+#    #+#             */
/*   Updated: 2019/10/28 14:30:38 by pcariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_str_join(char *str, char const *s1, char const *s2)
{
	int k;
	int i;

	k = 0;
	i = 0;
	while (s1[k])
	{
		str[i] = s1[k];
		k++;
		i++;
	}
	k = 0;
	while (s2[k])
	{
		str[i] = s2[k];
		k++;
		i++;
	}
	str[i] = '\0';
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char*str;
	int i;

	if (s1 == 0 || s2 == 0)
		return (0);
	i = (ft_strlen(s1) + ft_strlen(s2));
	if (!(str = malloc(sizeof(char) * i + 1)))
		return (0);
	ft_str_join(str, s1, s2);
	return (str);
}
