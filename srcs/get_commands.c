/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <pcariou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 09:40:21 by pcariou           #+#    #+#             */
/*   Updated: 2020/10/12 15:35:43 by pcariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int 	double_sep(char *buf)
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

int		find_sep(char c, t_cmd *cmd)
{
	if (c == ';' || c == '|')
	{
		cmd->sep = c;
		return (1);
	}
	return (0);
}

int		split_input(char *buf, char **words, t_cmd *cmd)
{
	int i;
	int c;
	int l;

	i = 0;
	c = 0;
	l = 0;
	while (buf[i])
	{
		if (!(ft_isspace(buf[i])))
		{
			while (buf[i] && !(ft_isspace(buf[i])))
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
	if (!cmd->next && cmd->sep == '|')
		return (0);
	return (1);
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
		while (buf[c] && ft_isspace(buf[c]))
			c++;
		while (buf[c] && !(ft_isspace(buf[c])))
		{
			c++;
			l++;
		}
		if (!(words[i] = malloc(sizeof(char) * (l + 1))))
			return ;
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
		if (!(ft_isspace(buf[i])))
		{
			c++;
			while (buf[i] && !(ft_isspace(buf[i])))
				i++;
		}
		else
			i++;
	}
	return (c);
}

/*
   void    better_input(char *buf)
   {
   int i;

   i = 0;
   while (buf[i] >= 31 && buf[i] < 127)
   i++;
   buf[i] = 0;
   }
 */

void	add_next(int c, t_cmd *cmd)
{
	t_cmd *next;

	if (c)
	{
		if (!(next = malloc(sizeof(t_cmd))))
			return ;
		next->sepl = cmd->sep;
		cmd->next = next;
	}
	else
		cmd->next = 0;	
}

void	cmd_line(char *buf, t_cmd *cmd)
{
	int i;
	int l;
	int k;

	i = 0;
	while (buf[i])
	{
		l = 0;
		k = 0;
		cmd->sep = 0;
		while (buf[i] && !find_sep(buf[i], cmd))
		{
			l++;
			i++;
		}
		cmd->line = malloc(sizeof(char) * (l + 1));
		i-=l;
		while (buf[i] && !find_sep(buf[i], cmd))
		{
			cmd->line[k] = buf[i];
			i++;
			k++;
		}
		cmd->line[k] = 0;
		i++;	
		add_next(buf[i], cmd);
		cmd = (buf[i]) ? cmd->next : cmd;
	}
}

int		read_input(t_cmd *cmd)
{
	//char buf[300];

	char *buf;
	int n;

	//read(0, buf, 300);
	get_next_line(0, &buf);
	if (!buf[0] || bad_beginning(buf) || double_sep(buf))
		return (0);
	cmd_line(buf, cmd);
	pipe_fd_reset(cmd);
	while (cmd)
	{
		cmd->nforks = 0;
		//better_input(buf);
		n = count_words(cmd->line);
		if (!(cmd->argv = malloc(sizeof(char *) * (n + 2))))
			return (0);
		cmd->argv[n] = 0;
		malloc_words(cmd->line, cmd->argv, n);
		if (!split_input(cmd->line, cmd->argv, cmd))
			return (0);
		cmd = cmd->next;
	}
	return (1);
}
