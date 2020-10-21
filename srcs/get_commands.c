/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <pcariou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 09:40:21 by pcariou           #+#    #+#             */
/*   Updated: 2020/10/21 12:24:21 by pcariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

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
		cmd->next->prev = cmd;
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

char	*real_env(char *envv, t_cmdv *cmdv)
{
	int i;
	int m;
	char *space;

	i = -1;
	if (envv[0] && envv[0] == '?' && !envv[1])
	{
		space = ft_itoa(cmdv->error_line);
		return (space);
	}
	while (cmdv->envp[++i])
	{
		m = 0;
		while (envv[m] && cmdv->envp[i][m] && envv[m] == cmdv->envp[i][m])
			m++;
		if (!envv[m] && cmdv->envp[i][m] && cmdv->envp[i][m] == '=' && cmdv->envp[i][m + 1])
			return (&cmdv->envp[i][m + 1]);
	}
	space = malloc(2);
	space[0] = ' ';
	space[1] = 0;
	return (space);
}

char	*buf_with_envv(char *buf, char *renvv, char *end, int length, int l)
{
	int i;
	int m;
	int k;
	char *ret;

	i = -1;
	m = 0;
	k = 0;
	if (!(ret = malloc(sizeof(char) * (ft_strlen(buf) + (ft_strlen(renvv) - (length - 1)) + 1))))
		return (0);
	while (++i < l)
		ret[m++] = buf[i];
	while (renvv[k])
		ret[m++] = renvv[k++];
	k = -1;
	while (end[++k])
		ret[m++] = end[k];
	ret[m] = 0;
//	free(buf);
	return (ret);
}

char	*get_envv(char *buf, t_cmdv *cmdv, int i)
{
	char *envv;
	char *end;
	char *renvv;
	int cp;
	int m;
	int length;
	//int r;
	int l;

	while (buf[++i])
	{
		if (buf[i] == '$' && buf[i + 1])
		{
			m = 0;
			l = i;
			cp = ++i;
			while (buf[i] && buf[i] != '/' && buf[i] != '$')
			{
				m++;
				i++;
			}
			if (!(envv = malloc(sizeof(char) * m + 1)))
				return (0);
			i = cp;
			m = 0;
			while (buf[i] && buf[i] != '/' && buf[i] != '$')
				envv[m++] = buf[i++];
			envv[m] = 0;
	//		r = i;
			end = &buf[i];
			length = ft_strlen(envv);
			renvv = real_env(envv, cmdv);
			//printf("%s\n", renvv);
			buf = buf_with_envv(buf, renvv, end, length, l);
			//free(renvv);
			free(envv);
			get_envv(buf, cmdv, i - 1);
		}
	}
	return (buf);
}

int		read_input(t_cmd *cmd, t_cmdv *cmdv)
{
	//char buf[300];

	char *buf;
	int n;

	//read(0, buf, 300);
	get_next_line(0, &buf);
	if (!buf[0] || bad_beginning(buf) || bad_ending(buf) || double_sep(buf)
		|| tripledouble_redir(buf))
		return (0);
	//buf = get_envv(buf, cmdv, -1);
	count_sep(buf, cmdv);
	cmd_line(buf, cmd, cmdv);
	count_redir(cmd);
	get_redirb(cmd);
	get_redir(cmd);
	if (empty_redir(cmd))
		return (0);
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
