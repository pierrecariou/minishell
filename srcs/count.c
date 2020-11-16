/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <pcariou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 10:02:52 by pcariou           #+#    #+#             */
/*   Updated: 2020/11/16 10:06:10 by pcariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	init_inquotes(t_cmdv *cmdv)
{
	cmdv->inquotes = 0;
	cmdv->inquotess = 0;
	cmdv->inquotesd = 0;
}

void	count_sep(char *buf, t_cmdv *cmdv)
{
	int i;
	int inquotes;

	i = -1;
	cmdv->nsep = 0;
	inquotes = 0;
	cmdv->inquotess = 0;
	cmdv->inquotesd = 0;
	while (buf[++i])
	{
		inquotes = is_inquotes(buf[i], cmdv);
		if ((buf[i] == '|' || buf[i] == ';')
				&& inquotes == 0)
			cmdv->nsep++;
	}
}

void	count_envv(char *buf, t_cmdv *cmdv)
{
	int i;
	int m;

	i = -1;
	m = -1;
	cmdv->nenvv = 0;
	cmdv->inquotesd = 0;
	cmdv->inquotess = 0;
	while (buf[++i])
		cmdv->nenvv = (buf[i] == '$') ? cmdv->nenvv + 1 : cmdv->nenvv;
	if (!cmdv->nenvv)
		return ;
	if (!(cmdv->envreplace = malloc(sizeof(int) * cmdv->nenvv)))
		return ;
	i = -1;
	while (buf[++i])
	{
		is_inquotes(buf[i], cmdv);
		if (buf[i] == '$' && cmdv->inquotess)
			cmdv->envreplace[++m] = 0;
		else if (buf[i] == '$')
			cmdv->envreplace[++m] = 1;
	}
}
