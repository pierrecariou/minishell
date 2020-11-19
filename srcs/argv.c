/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <pcariou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 10:07:31 by pcariou           #+#    #+#             */
/*   Updated: 2020/11/19 11:50:41 by pcariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int		split_input1(t_cmd *cmd, t_cmdv *cmdv, int i, int c)
{
	if (cmd->line[i] && (!ft_isspace(cmd->line[i]) || cmdv->inquotes)
		&& !cmdv->isaquote)
	{
		while ((cmd->line[i] && !ft_isspace(cmd->line[i]) &&
					cmdv->inquotes == 0) || (cmdv->inquotes == 1
					&& cmd->line[i]))
		{
			cmdv->inquotes = is_inquotes(cmd->line[i], cmdv);
			if (!cmdv->isaquote)
				cmd->argv[c][cmdv->l++] = cmd->line[i];
			i++;
		}
		if (cmdv->l > 0)
			cmd->argv[c][cmdv->l] = 0;
	}
	return (i);
}

int		split_input(t_cmd *cmd, t_cmdv *cmdv)
{
	int i;
	int c;

	i = 0;
	c = -1;
	init_inquotes(cmdv);
	while (cmd->line[i] && c < cmd->n)
	{
		cmdv->l = 0;
		while (cmd->line[i] && ft_isspace(cmd->line[i]) && !cmdv->inquotes)
			i++;
		cmdv->inquotes = is_inquotes(cmd->line[i], cmdv);
		if (cmd->line[i] && (!ft_isspace(cmd->line[i]) ||
			cmdv->inquotes) && !cmdv->isaquote)
			c++;
		i = split_input1(cmd, cmdv, i, c);
		if (cmd->line[i])
			i++;
	}
	if (!cmd->next && cmd->sep == '|')
		return (0);
	return (1);
}

int		malloc_words1(t_cmd *cmd, t_cmdv *cmdv, int i, int k)
{
	if (cmd->line[i] && (!ft_isspace(cmd->line[i]) ||
		cmdv->inquotes) && !cmdv->isaquote)
	{
		while ((cmd->line[i] && !ft_isspace(cmd->line[i]) &&
					cmdv->inquotes == 0) || (cmdv->inquotes == 1 &&
					cmd->line[i]))
		{
			cmdv->inquotes = is_inquotes(cmd->line[i], cmdv);
			if (!cmdv->isaquote)
				cmdv->l++;
			i++;
		}
		if (cmdv->l > 0)
			if (!(cmd->argv[k++] = malloc(sizeof(char) * (cmdv->l + 1))))
				return (0);
	}
	return (i);
}

void	malloc_words(t_cmd *cmd, t_cmdv *cmdv)
{
	int i;
	int k;

	i = 0;
	k = 0;
	init_inquotes(cmdv);
	while (cmd->line[i] && k < cmd->n)
	{
		cmdv->l = 0;
		while (cmd->line[i] && ft_isspace(cmd->line[i]) && !cmdv->inquotes)
			i++;
		cmdv->inquotes = is_inquotes(cmd->line[i], cmdv);
		i = malloc_words1(cmd, cmdv, i, k);
		k = (cmdv->l > 0) ? k + 1 : k;
		if (cmd->line[i])
			i++;
	}
}

int		count_words(char *buf, t_cmdv *cmdv)
{
	int c;
	int i;

	c = 0;
	i = 0;
	init_inquotes(cmdv);
	while (buf[i])
	{
		cmdv->inquotes = is_inquotes(buf[i], cmdv);
		while (buf[i] && ft_isspace(buf[i]))
			i++;
		if (buf[i] && !ft_isspace(buf[i]) && !cmdv->isaquote)
		{
			c++;
			while ((buf[i] && !ft_isspace(buf[i]) && cmdv->inquotes == 0) ||
					(cmdv->inquotes == 1 && buf[i]))
			{
				cmdv->inquotes = is_inquotes(buf[i], cmdv);
				i++;
			}
		}
		if (buf[i])
			i++;
	}
	return (c);
}
