/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <pcariou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 09:40:21 by pcariou           #+#    #+#             */
/*   Updated: 2020/11/13 17:28:09 by pcariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	init_inquotes(t_cmdv *cmdv)
{
	cmdv->inquotes = 0;
	cmdv->inquotess = 0;
	cmdv->inquotesd = 0;
}

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

int		split_input1(t_cmd *cmd, t_cmdv *cmdv, int i, int c)
{
	if (cmd->line[i] && !ft_isspace(cmd->line[i]) && !cmdv->isaquote)
	{
		while ((cmd->line[i] && !ft_isspace(cmd->line[i]) &&
			cmdv->inquotes == 0) || (cmdv->inquotes == 1 && cmd->line[i]))
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
		cmdv->inquotes = is_inquotes(cmd->line[i], cmdv);
		while (cmd->line[i] && ft_isspace(cmd->line[i]))
			i++;
		if (cmd->line[i] && !ft_isspace(cmd->line[i]) && !cmdv->isaquote)
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
	if (cmd->line[i] && !ft_isspace(cmd->line[i]) && !cmdv->isaquote)
	{
		while ((cmd->line[i] && !ft_isspace(cmd->line[i]) &&
				cmdv->inquotes == 0) || (cmdv->inquotes == 1 && cmd->line[i]))
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

void		malloc_words(t_cmd *cmd, t_cmdv *cmdv)
{
	int i;
	int k;

	i = 0;
	k = 0;
	init_inquotes(cmdv);
	while (cmd->line[i] && k < cmd->n)
	{
		cmdv->l = 0;
		cmdv->inquotes = is_inquotes(cmd->line[i], cmdv);
		while (cmd->line[i] && ft_isspace(cmd->line[i]))
			i++;
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

void	init(t_cmd *cmd)
{
	t_cmd *cp;

	cp = cmd;
	while (cp)
	{
		cp->fdredir = -1;
		cp->argv = NULL;
		cp->pid = NULL;
		cp->redirf = NULL;
		cp->redirfl = NULL;
		cp->redirfb = NULL;
		cp = cp->next;
	}
}

void	free_paths(char **paths, char **envp, int loop)
{
	int i;

	if (loop != 2 && paths)
	{
		i = -1;
		while (paths[++i])
			free(paths[i]);
		free(paths);
	}
	if (!loop || loop == 2)
	{
		i = -1;
		while (envp[++i])
			free(envp[i]);
		free(envp);
	}
}

void	call_gnl(t_cmd *cmd, t_cmdv *cmdv, char **paths, char **envp)
{
	int		ret;
	char	*buf_cp;

	cmdv->buf = NULL;
	buf_cp = NULL;
	while (!(ret = get_next_line(0, &cmdv->buf)) && cmdv->buf)
	{
		buf_cp = cmdv->buf;
		cmdv->buf = NULL;
	}
	if (ret == 1 && buf_cp != NULL)
		cmdv->buf = buf_cp;
	if (!ret && !cmdv->buf)
	{
		free(cmd);
		free(cmdv);
		free_paths(paths, envp, 2);
		ft_putstr_fd("exit\n", 1);
		exit(0);
	}
	cmdv->empty = (cmdv->buf[0]) ? 0 : 1;
}

void	fill_argv(t_cmd *cmd, t_cmdv *cmdv)
{
	while (cmd)
	{
		cmd->active = 1;
		cmd->nforks = 0;
		cmd->n = count_words(cmd->line, cmdv);
		if (!(cmd->argv = malloc(sizeof(char *) * (cmd->n + 1))))
			return ;
		malloc_words(cmd, cmdv);
		if (!split_input(cmd, cmdv))
			return ;
		cmd->argv[cmd->n] = 0;
		cmd = cmd->next;
	}
}

int		read_input(t_cmd *cmd, t_cmdv *cmdv, char **paths, char **envp)
{
	call_gnl(cmd, cmdv, paths, envp);
	if (!cmdv->buf[0] || bad_beginning(cmdv->buf) || bad_ending(cmdv->buf) ||
			double_sep(cmdv->buf) || tripledouble_redir(cmdv->buf) ||
			quotes_not_closed(cmdv->buf))
	{
		free(cmdv->buf);
		return (0);
	}
	count_envv(cmdv->buf, cmdv);
	count_sep(cmdv->buf, cmdv);
	cmd_line(cmdv->buf, cmd, cmdv);
	free(cmdv->buf);
	init(cmd);
	count_redir(cmd, cmdv);
	get_redirb(cmd, cmdv);
	get_redir(cmd, cmdv);
	if (empty_redir(cmd))
		return (0);
	pipe_fd_reset(cmd);
	fill_argv(cmd, cmdv);
	fork_error(cmdv);
	return (1);
}
