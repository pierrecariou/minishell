/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <pcariou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 11:34:16 by pcariou           #+#    #+#             */
/*   Updated: 2020/10/15 11:35:10 by pcariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int             get_redirfb(t_cmd *cmd, int i, int c)
{
	int cp;
	int l;

	l = 0;
	while (ft_isspace(cmd->line[i]))
		i++;
	cp = i;
	while (cmd->line[i] && !ft_isspace(cmd->line[i]) && cmd->line[i] != '>')
	{
		l++;
		i++;
	}
	if (!(cmd->redirfb[c] = malloc(sizeof(char) * (l + 1))))
		return (0);
	l = 0;
	while (cmd->line[cp] && !ft_isspace(cmd->line[cp]) && cmd->line[cp] != '>')
	{
		cmd->redirfb[c][l] = cmd->line[cp];
		cmd->line[cp] = ' ';
		cp++;
		l++;
	}
	cmd->redirfb[c][l] = 0;
	return (cp);
}

void    get_redirb(t_cmd *cmd)
{
	int i;
	int c;

	while (cmd)
	{
		i = -1;
		c = 0;
		if (cmd->nredir > 1)
		{
			if (!(cmd->redirfb = malloc(sizeof(char *) * cmd->nredir)))
				return ;
			cmd->redirfb[cmd->nredir - 1] = 0;
			while (cmd->line[++i] && c < (cmd->nredir - 1))
			{
				if (cmd->line[i] == '>')
				{
					cmd->line[i] = ' ';
					i++;
					if (cmd->line[i] == '>')
						cmd->line[i++] = ' ';
					i = get_redirfb(cmd, i, c) - 1;
					c++;
				}
			}
		}
		cmd = cmd->next;
	}
}

void    count_redir(t_cmd *cmd)
{
	int i;

	while (cmd)
	{
		i = -1;
		cmd->nredir = 0;
		while (cmd->line[++i])
		{
			if (cmd->line[i] == '>')
			{
				i++;
				if (cmd->line[i] == '>')
					i++;
				cmd->nredir++;
			}
		}
		cmd = cmd->next;
	}
}

void    get_redirf(t_cmd *cmd, int i)
{
	int cp;
	int l;

	l = 0;
	while (ft_isspace(cmd->line[i]))
		i++;
	cp = i;
	while (cmd->line[i] && !(ft_isspace(cmd->line[i])))
	{
		l++;
		i++;
	}
	if (!(cmd->redirf = malloc(sizeof(char) * (l + 1))))
		return ;
	l = 0;
	while (cmd->line[cp] && !(ft_isspace(cmd->line[cp])))
	{
		cmd->redirf[l] = cmd->line[cp];
		cmd->line[cp] = ' ';
		cp++;
		l++;
	}
	cmd->redirf[l] = 0;
}

void    get_redir(t_cmd *cmd)
{
	int i;

	while (cmd)
	{
		i = -1;
		cmd->redir = 0;
		while (cmd->line[++i])
		{
			if (cmd->line[i] == '<' || cmd->line[i] == '>')
			{
				cmd->redir = cmd->line[i];
				cmd->line[i] = ' ';
				if (cmd->line[i + 1] && cmd->line[i + 1] == '>')
				{
					cmd->redir = '}';
					cmd->line[i + 1] = ' ';
				}
				get_redirf(cmd, i);
			}
		}
		cmd = cmd->next;
	}
}
