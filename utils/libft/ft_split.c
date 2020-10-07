/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 18:03:23 by pcariou           #+#    #+#             */
/*   Updated: 2019/10/28 16:00:51 by pcariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		check_c(char a, char c)
{
	if (a == c)
		return (1);
	return (0);
}

int		count_words(char *str, char c)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && check_c(str[i], c) == 1)
			i++;
		while (str[i] && check_c(str[i], c) == 0)
			i++;
		if (check_c(str[i - 1], c) == 0)
			count++;
	}
	return (count + 1);
}

void	create_words(char **strs, char *str, char c)
{
	int i;
	int l;
	int k;

	i = 0;
	l = 0;
	while (str[i])
	{
		k = 0;
		while (str[i] && check_c(str[i], c) == 1)
			i++;
		while (str[i + k] && check_c(str[i + k], c) == 0)
			k++;
		if (!(strs[l] = malloc(sizeof(char) * k + 1)))
			return ;
		k = 0;
		while (str[i] && check_c(str[i], c) == 0)
		{
			strs[l][k] = str[i];
			k++;
			i++;
		}
		strs[l][k] = '\0';
		l++;
	}
}

char	**tab_nul(void)
{
	char **tab;

	if (!(tab = malloc(sizeof(char *) * 1)))
		return (0);
	tab[0] = 0;
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	char	*str;
	char	**strs;
	int		count;

	if (s == 0 || s[0] == 0)
		return (tab_nul());
	str = (char *)s;
	count = count_words(str, c);
	if (!(strs = malloc(sizeof(char *) * count)))
		return (0);
	create_words(strs, str, c);
	strs[count - 1] = 0;
	return (strs);
}
