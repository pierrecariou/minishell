/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 15:28:52 by pcariou           #+#    #+#             */
/*   Updated: 2020/06/10 18:52:24 by pcariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_str_join(char *s, char *s1, char *s2)
{
	int k;
	int i;

	k = 0;
	i = 0;
	while (s1[k])
	{
		s[i] = s1[k];
		k++;
		i++;
	}
	k = 0;
	while (s2[k])
	{
		s[i] = s2[k];
		k++;
		i++;
	}
	s[i] = '\0';
}

char	*ft_strjoin(char *s1, char *s2)
{
	char*s;
	int i;
	int l;

	i = 0;
	l = 0;
	while (s1[i])
		i++;
	while (s2[l])
		l++;
	if (!(s = malloc(sizeof(char) * (i + l) + 1)))
		return (0);
	ft_str_join(s, s1, s2);
	if (s1[0] != 0)
		free(s1);
	free(s2);
	return (s);
}

char	*create_line(char *buf, int b, int e, char *line_cut)
{
	char	*s;
	int		i;

	i = 0;
	if (!(s = malloc(sizeof(char) * e + 2)))
		return (0);
	while (b <= e)
	{
		s[i] = buf[b];
		i++;
		b++;
	}
	s[i] = 0;
	if (line_cut != NULL)
		s = ft_strjoin(line_cut, s);
	return (s);
}

int		count_lines(char *buf)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (buf[i])
	{
		if (buf[i] == '\n')
			count++;
		i++;
	}
	return (count);
}
