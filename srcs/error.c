/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <pcariou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 16:32:57 by pcariou           #+#    #+#             */
/*   Updated: 2020/10/14 16:43:15 by pcariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int     double_sep(char *buf)
{
	int i;

	i = -1;
	while (buf[++i])
	{
		if ((buf[i] == '|' || buf[i] == ';') &&
				(buf[i + 1] && (buf[i+1] == '|' ||
								buf[i+1] == ';')))
			return (1);
	}
	return (0);
}

int             bad_beginning(char *buf)
{
	int i;

	i = 0;
	while (ft_isspace(buf[i]))
		i++;
	if (buf[i] == '|' || buf[i] == ';')
		return (1);
	return (0);
}

int			tripledouble_redir(char *buf)
{
	int i;
	int cr;
	int space;

	i = -1;
	space = 0;
	cr = 0;
	while (buf[++i])
	{
		if (buf[i] == '>')
			cr++;
		if (cr == 1 && ft_isspace(buf[i]))
			space = 1;
		
		if (!ft_isspace(buf[i]) && buf[i] != '>')
			cr = 0;
	//	printf("%c -- space : %d -- cr : %d\n", buf[i], space, cr);
		if (cr > 2 || (cr == 2 && space == 1))
			return (1);
		if (cr != 1)
			space = 0;
	}
	return (0);
}
