/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <pcariou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 09:40:21 by pcariou           #+#    #+#             */
/*   Updated: 2020/10/07 10:05:29 by pcariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char	**read_input(void)
{
	//char buf[300];
	int n;
	char *buf;
	char **words;

	//read(0, buf, 300);
	(void)n;
	get_next_line(0, &buf);
	better_input(buf);
	n = count_words(buf);
	words = malloc(sizeof(char *) * (n + 1));
	words[n] = 0;
	malloc_words(buf, words, n);
	split_input(buf, words);
	/*
	   int i = -1;
	   while (words[++i])
	   printf("%s\n", words[i]);
	 */
	//check_input(buf);
	return (words);
}

void    split_input(char *buf, char **words)
{
	int i;
	int c;
	int l;

	i = 0;
	c = 0;
	l = 0;
	while (buf[i])
	{
		if (buf[i] != ' ')
		{
			while (buf[i] && buf[i] != ' ')
			{
				words[c][l] = buf[i];
				i++;
				l++;
			}
			words[c][l] = 0;
			c++;
		}
		else
			i++;
		l = 0;
	}
}

void    malloc_words(char *buf, char **words, int n)
{
	int i;
	int c;
	int l;

	i = -1;
	c = 0;
	l = 0;
	while (++i < n)
	{
		while (buf[c] && buf[c] == ' ')
			c++;
		while (buf[c] && buf[c] != ' ')
		{
			c++;
			l++;
		}
		words[i] = malloc(sizeof(char) * (l + 1));
		l = 0;
	}
}

int             count_words(char *buf)
{
	int i;
	int c;

	i = 0;
	c = 0;
	while (buf[i])
	{
		if (buf[i] != ' ')
		{
			c++;
			while (buf[i] && buf[i] != ' ')
				i++;
		}
		else
			i++;
	}
	return (c);
}

void    better_input(char *buf)
{
	int i;

	i = 0;
	while (buf[i] > 31 && buf[i] < 127)
		i++;
	buf[i] = 0;
}
