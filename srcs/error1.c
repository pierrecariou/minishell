/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <pcariou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 19:11:58 by pcariou           #+#    #+#             */
/*   Updated: 2020/11/16 11:37:17 by pcariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int		quotes_not_closed(char *buf)
{
	int i;
	int inquotes_d;
	int inquotes_s;

	i = -1;
	inquotes_d = 0;
	inquotes_s = 0;
	while (buf[++i])
	{
		if (inquotes_d == 0 && buf[i] == '\"' && inquotes_s == 0)
			inquotes_d = 1;
		else if (inquotes_s == 0 && buf[i] == '\'' && inquotes_d == 0)
			inquotes_s = 1;
		else if (buf[i] == '\"' && inquotes_s == 0)
			inquotes_d = 0;
		else if (buf[i] == '\'' && inquotes_d == 0)
			inquotes_s = 0;
	}
	if (inquotes_s != 0 || inquotes_d != 0)
		return (1);
	return (0);
}

int		fork_error1(t_cmd *cp, int i)
{
	cp->active = 0;
	cp = cp->prev;
	while (--i > 0 && cp->sep && cp->sep == '|')
	{
		cp->active = 0;
		cp = cp->prev;
	}
	return (i);
}

void	fork_error(t_cmdv *cmdv)
{
	t_cmd	*cp;
	t_cmd	*cp1;
	int		n;
	int		i;

	cp = cmdv->cp;
	n = 0;
	while (cp)
	{
		cp1 = cp;
		n++;
		if (cp->argv[0] && no_fork(cp->argv) && cp->sepl && cp->sepl == '|')
		{
			i = n;
			i = fork_error1(cp, i);
			cp = cp1;
		}
		if (cp->argv[0] && no_fork(cp->argv) && cp->sep && cp->sep == '|')
		{
			cp->sep = ';';
			cp->active = 0;
		}
		cp = cp->next;
	}
}
