/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <pcariou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 09:41:05 by pcariou           #+#    #+#             */
/*   Updated: 2020/11/16 10:27:44 by pcariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int		find_sep(char *buf, t_cmd *cmd, int i, int inquotes)
{
	if (buf[i] == ';' || buf[i] == '|')
	{
		if (inquotes == 1)
			return (0);
		cmd->sep = buf[i];
		return (1);
	}
	return (0);
}

int		is_inquotes(char c, t_cmdv *cmdv)
{
	cmdv->isaquote = 0;
	if (cmdv->inquotesd == 0 && c == '\"' && cmdv->inquotess == 0)
		cmdv->inquotesd = 1;
	else if (cmdv->inquotess == 0 && c == '\'' && cmdv->inquotesd == 0)
		cmdv->inquotess = 1;
	else if (c == '\"' && cmdv->inquotess == 0)
		cmdv->inquotesd = 0;
	else if (c == '\'' && cmdv->inquotesd == 0)
		cmdv->inquotess = 0;
	else
		return (cmdv->inquotess + cmdv->inquotesd);
	cmdv->isaquote = 1;
	return (cmdv->inquotess + cmdv->inquotesd);
}

void	add_next(int m, t_cmd *cmd, t_cmdv *cmdv)
{
	t_cmd *next;

	if (m == 0)
		cmd->sepl = 0;
	if (m + 1 < cmdv->nsep + 1)
	{
		if (!(next = malloc(sizeof(t_cmd))))
			return ;
		next->sepl = cmd->sep;
		cmd->next = next;
		cmd->next->prev = cmd;
	}
	else
		cmd->next = 0;
}

int		cmd_line1(char *buf, t_cmd *cmd, t_cmdv *cmdv, int i)
{
	int l;
	int k;

	l = 0;
	k = 0;
	cmd->sep = 0;
	while (buf[i] && !find_sep(buf, cmd, i, cmdv->inquotes))
	{
		cmdv->inquotes = is_inquotes(buf[i], cmdv);
		l++;
		i++;
	}
	cmd->line = malloc(sizeof(char) * (l + 1));
	i -= l;
	while (buf[i] && !find_sep(buf, cmd, i, cmdv->inquotes))
	{
		cmdv->inquotes = is_inquotes(buf[i], cmdv);
		cmd->line[k] = buf[i];
		i++;
		k++;
	}
	cmd->line[k] = 0;
	i++;
	return (i);
}

void	cmd_line(char *buf, t_cmd *cmd, t_cmdv *cmdv)
{
	int i;
	int m;

	i = 0;
	m = -1;
	while (++m < cmdv->nsep + 1)
	{
		cmdv->inquotes = 0;
		cmdv->inquotess = 0;
		cmdv->inquotesd = 0;
		i = cmd_line1(buf, cmd, cmdv, i);
		add_next(m, cmd, cmdv);
		cmd = cmd->next;
	}
}
