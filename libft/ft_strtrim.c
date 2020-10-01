/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 16:51:30 by pcariou           #+#    #+#             */
/*   Updated: 2019/10/28 19:18:15 by pcariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		check_set(char a, char const *set)
{
	int i;

	i = 0;
	while (set[i])
	{
		if (set[i] == a)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_str_create(char *str, char const *s1, char const *set, int end)
{
	int		i;
	size_t	l;

	i = 0;
	l = 0;
	while (check_set(s1[l], set) == 1)
		l++;
	while (l <= (ft_strlen(s1) - end - 1))
	{
		str[i] = s1[l];
		l++;
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*empty_string(void)
{
	char *str;

	if (!(str = malloc(sizeof(char) * 1)))
		return (0);
	str[0] = '\0';
	return (str);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		count;
	char	*str;
	size_t	end;

	i = 0;
	end = 0;
	if (s1 == 0 || set == 0)
		return (0);
	count = ft_strlen(s1);
	while (check_set(s1[i], set) == 1)
		i++;
	if ((int)ft_strlen(s1) == i)
		return (empty_string());
	while (check_set(s1[count - 1], set) == 1)
	{
		i++;
		count--;
		end++;
	}
	if (!(str = malloc(sizeof(char) * (ft_strlen(s1) - i + 1))))
		return (0);
	return (ft_str_create(str, s1, set, end));
}
