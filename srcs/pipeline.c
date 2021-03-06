/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <pcariou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 13:55:56 by pcariou           #+#    #+#             */
/*   Updated: 2020/11/17 09:34:11 by pcariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	pipe_fd_reset(t_cmd *cmd)
{
	while (cmd)
	{
		cmd->fdin = -1;
		cmd->fdout = -1;
		cmd = cmd->next;
	}
}

void	store_pid(t_cmd *cmd, int pid)
{
	int i;

	i = 0;
	cmd->next->nforks = cmd->nforks + 1;
	if (!(cmd->next->pid = malloc(sizeof(int) * cmd->next->nforks)))
		return ;
	while (i < cmd->nforks)
	{
		cmd->next->pid[i] = cmd->pid[i];
		i++;
	}
	cmd->next->pid[i] = pid;
}

void	close_fd(t_cmdv *cmdv)
{
	t_cmd *cp;

	cp = cmdv->cp;
	while (cp->next)
	{
		if (cp->fdout != -1)
			close(cp->fdout);
		if (cp->next->fdin != -1)
			close(cp->next->fdin);
		cp = cp->next;
	}
}

void	pipeline1(t_cmd *cmd, char *file, t_cmdv *cmdv, int pid)
{
	if (pid == 0)
	{
		if (cmd->sepl == '|')
			dup2(cmd->fdin, 0);
		if (cmd->sep == '|')
			dup2(cmd->fdout, 1);
		close_fd(cmdv);
		exec_built(file, cmd->argv, cmd, cmdv);
		exit(0);
	}
}

void	pipeline(t_cmd *cmd, char *file, t_cmdv *cmdv)
{
	int pid;
	int i;
	int status;

	i = -1;
	status = 0;
	pid = fork();
	pipeline1(cmd, file, cmdv, pid);
	if (cmd->sep == '|')
		store_pid(cmd, pid);
	else
	{
		close_fd(cmdv);
		while (++i < cmd->nforks)
			waitpid(cmd->pid[i], &status, 0);
		waitpid(pid, &status, 0);
	}
	cmdv->error_line = status;
}
