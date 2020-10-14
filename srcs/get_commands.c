/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <pcariou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 09:40:21 by pcariou           #+#    #+#             */
/*   Updated: 2020/10/14 16:06:49 by pcariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int		get_redirfb(t_cmd *cmd, int i, int c)
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

void	get_redirb(t_cmd *cmd)
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

void	count_redir(t_cmd *cmd)
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

void	get_redir(t_cmd *cmd)
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

void	add_next(int m, t_cmd *cmd, t_cmdv *cmdv)
{
	t_cmd *next;

	if (m + 1 < cmdv->nsep + 1)
	{
		if (!(next = malloc(sizeof(t_cmd))))
			return ;
		next->sepl = cmd->sep;
		cmd->next = next;
	}
	else
		cmd->next = 0;	
}

void	cmd_line(char *buf, t_cmd *cmd, t_cmdv *cmdv)
{
	int i;
	int l;
	int k;
	int m;

	i = 0;
	m = -1;
	while (++m < cmdv->nsep + 1)
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
		add_next(m, cmd, cmdv);
		cmd = (buf[i]) ? cmd->next : cmd;
	}
}

void	count_sep(char *buf, t_cmdv *cmdv)
{
	int i;

	i = -1;
	cmdv->nsep = 0;
	while (buf[++i])
	{
		if (buf[i] == '|' || buf[i] == ';')
			cmdv->nsep++;
	}
}

int		read_input(t_cmd *cmd, t_cmdv *cmdv)
{
	//char buf[300];

	char *buf;
	int n;

	//read(0, buf, 300);
	get_next_line(0, &buf);
	if (!buf[0] || bad_beginning(buf) || double_sep(buf)
		|| tripledouble_redir(buf))
		return (0);
	count_sep(buf, cmdv);
	cmd_line(buf, cmd, cmdv);
	count_redir(cmd);
	get_redirb(cmd);
	get_redir(cmd);
	pipe_fd_reset(cmd);
	while (cmd)
	{
		//printf("%d\n", cmd->nredir);
		/*
		if (cmd->nredir > 1)
		{
			int i = 0;
			while (cmd->redirfb[i])
			{
				printf("%s\n", cmd->redirfb[i]);
				i++;
			}
		}
		*/
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
