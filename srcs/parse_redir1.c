/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <pcariou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 09:36:08 by pcariou           #+#    #+#             */
/*   Updated: 2020/11/17 09:37:46 by pcariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int		get_redirfb1(t_cmd *cmd, int c, int cp, int l)
{
	int i;

	i = 0;
	while (i < l)
	{
		cmd->redirfb[c][i] = cmd->line[cp];
		cmd->line[cp] = ' ';
		cp++;
		i++;
	}
	cmd->redirfb[c][i] = 0;
	return (cp);
}

int		get_redirfb(t_cmd *cmd, t_cmdv *cmdv, int i, int c)
{
	int cp;
	int l;
	int inquotes;

	l = 0;
	inquotes = cmdv->inquotess + cmdv->inquotesd;
	while (ft_isspace(cmd->line[i]))
		i++;
	cp = i;
	while (cmd->line[i] && !ft_isspace(cmd->line[i]) &&
			(cmd->line[i] != '>' || inquotes))
	{
		inquotes = is_inquotes(cmd->line[i], cmdv);
		l++;
		i++;
	}
	if (!(cmd->redirfb[c] = malloc(sizeof(char) * (l + 1))))
		return (0);
	cp = get_redirfb1(cmd, c, cp, l);
	return (cp);
}

int		get_redirb1(t_cmd *cmd, t_cmdv *cmdv, int i, int c)
{
	cmd->line[i++] = ' ';
	cmdv->inquotes = is_inquotes(cmd->line[i], cmdv);
	if (cmd->line[i] == '>' && !cmdv->inquotes)
		cmd->line[i++] = ' ';
	cmdv->inquotes = is_inquotes(cmd->line[i], cmdv);
	i = get_redirfb(cmd, cmdv, i, c) - 1;
	return (i);
}

void	get_redirb(t_cmd *cmd, t_cmdv *cmdv)
{
	int i;
	int c;

	while (cmd)
	{
		init_inquotes(cmdv);
		i = -1;
		c = 0;
		if (cmd->nredir > 1)
		{
			if (!(cmd->redirfb = malloc(sizeof(char *) * cmd->nredir)))
				return ;
			cmd->redirfb[cmd->nredir - 1] = 0;
			while (cmd->line[++i] && c < (cmd->nredir - 1))
			{
				cmdv->inquotes = is_inquotes(cmd->line[i], cmdv);
				if (cmd->line[i] == '>' && !cmdv->inquotes)
					get_redirb1(cmd, cmdv, i, c++);
			}
		}
		cmd = cmd->next;
	}
}
