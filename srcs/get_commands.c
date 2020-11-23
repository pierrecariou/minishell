/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <pcariou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 09:40:21 by pcariou           #+#    #+#             */
/*   Updated: 2020/11/23 16:20:47 by pcariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

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
		ft_putstr_fd("exit\n", 0);
		exit(cmdv->error_line);
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
	cmdv->no_line = (!cmdv->buf[0]) ? 1 : 0;
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
