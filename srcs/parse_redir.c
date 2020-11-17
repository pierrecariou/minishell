/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <pcariou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 11:34:16 by pcariou           #+#    #+#             */
/*   Updated: 2020/11/17 09:56:09 by pcariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	count_redir(t_cmd *cmd, t_cmdv *cmdv)
{
	int i;
	int inquotes;

	while (cmd)
	{
		inquotes = 0;
		cmdv->inquotesd = 0;
		cmdv->inquotess = 0;
		i = -1;
		cmd->nredir = 0;
		while (cmd->line[++i])
		{
			inquotes = is_inquotes(cmd->line[i], cmdv);
			if (cmd->line[i] == '>' && !inquotes)
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

void	get_redirfl(t_cmd *cmd, int i)
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
	if (!(cmd->redirfl = malloc(sizeof(char) * (l + 1))))
		return ;
	l = 0;
	while (cmd->line[cp] && !(ft_isspace(cmd->line[cp])))
	{
		cmd->redirfl[l] = cmd->line[cp];
		cmd->line[cp] = ' ';
		cp++;
		l++;
	}
	cmd->redirfl[l] = 0;
}

void	get_redirf(t_cmd *cmd, int i)
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

void	get_redir1(t_cmd *cmd, int i)
{
	if (cmd->line[i] == '<')
		cmd->redirl = cmd->line[i];
	else
		cmd->redir = cmd->line[i];
	if (cmd->line[i + 1] && cmd->line[i + 1] == '>')
	{
		cmd->redir = '}';
		cmd->line[i + 1] = ' ';
	}
	if (cmd->line[i] == '>')
		get_redirf(cmd, i + 1);
	else if (cmd->line[i] == '<')
		get_redirfl(cmd, i + 1);
	cmd->line[i] = ' ';
}

void	get_redir(t_cmd *cmd, t_cmdv *cmdv)
{
	int i;

	while (cmd)
	{
		init_inquotes(cmdv);
		i = -1;
		cmd->redir = 0;
		cmd->redirl = 0;
		while (cmd->line[++i])
		{
			cmdv->inquotes = is_inquotes(cmd->line[i], cmdv);
			if ((cmd->line[i] == '<' || cmd->line[i] == '>') && !cmdv->inquotes)
				get_redir1(cmd, i);
		}
		cmd = cmd->next;
	}
}
