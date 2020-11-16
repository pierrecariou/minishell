/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <pcariou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 16:32:57 by pcariou           #+#    #+#             */
/*   Updated: 2020/11/16 11:43:02 by pcariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int		double_sep(char *buf)
{
	int i;
	int csep;

	i = -1;
	csep = 0;
	while (buf[++i])
	{
		if (buf[i] == '|' || buf[i] == ';')
			csep++;
		if (!ft_isspace(buf[i]) && buf[i] != '|' && buf[i] != ';')
			csep = 0;
		if (csep > 1)
			return (1);
	}
	return (0);
}

int		bad_beginning(char *buf)
{
	int i;

	i = 0;
	while (ft_isspace(buf[i]))
		i++;
	if (buf[i] == '|' || buf[i] == ';')
		return (1);
	return (0);
}

int		bad_ending(char *buf)
{
	int i;

	i = ft_strlen(buf) - 1;
	while (ft_isspace(buf[i]))
		i--;
	if (buf[i] == ';')
		buf[i] = ' ';
	if (buf[i] == '|')
		return (1);
	return (0);
}

int		tripledouble_redir(char *buf)
{
	int i;
	int cr;
	int space;

	i = -1;
	space = 0;
	cr = 0;
	while (buf[++i])
	{
		if (buf[i] == '>' || buf[i] == '<')
			cr++;
		if (cr == 1 && ft_isspace(buf[i]))
			space = 1;
		if (!ft_isspace(buf[i]) && buf[i] != '>' && buf[i] != '<')
			cr = 0;
		if (cr > 2 || (cr == 2 && space == 1))
			return (1);
		if (cr != 1)
			space = 0;
	}
	return (0);
}

int		empty_redir(t_cmd *cmd)
{
	while (cmd)
	{
		if ((cmd->redir == '>' || cmd->redir == '}' || cmd->redir == '<')
			&& !cmd->redirf[0])
			return (1);
		cmd = cmd->next;
	}
	return (0);
}
