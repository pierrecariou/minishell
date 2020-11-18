/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <pcariou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 09:26:49 by pcariou           #+#    #+#             */
/*   Updated: 2020/11/17 15:55:41 by pcariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	quithandler(int num)
{
	(void)num;
	ft_putstr_fd("\33[2D", 0);
	ft_putstr_fd("  ", 0);
	ft_putstr_fd("\33[2D", 0);
	return ;
}

void	free_structs1(t_cmdv *cmdv)
{
	int i;

	i = -1;
	if (cmdv->cp->line)
		free(cmdv->cp->line);
	while (cmdv->cp->argv && cmdv->cp->argv[++i])
		free(cmdv->cp->argv[i]);
	if (cmdv->cp->argv)
		free(cmdv->cp->argv);
	if (cmdv->cp->pid)
		free(cmdv->cp->pid);
	if (cmdv->cp->redirf)
		free(cmdv->cp->redirf);
	if (cmdv->cp->redirfl)
		free(cmdv->cp->redirfl);
	i = -1;
	while (cmdv->cp->redirfb && cmdv->cp->redirfb[++i])
		free(cmdv->cp->redirfb[i]);
	if (cmdv->cp->redirfb)
		free(cmdv->cp->redirfb);
}

void	free_structs(t_cmdv *cmdv)
{
	t_cmd *cp;

	while (cmdv->cp)
	{
		free_structs1(cmdv);
		cp = cmdv->cp;
		cmdv->cp = cmdv->cp->next;
		free(cp);
	}
	if (cmdv->envreplace)
		free(cmdv->envreplace);
	free(cmdv);
}

void	init_loop(t_cmd *cmd, t_cmdv *cmdv, char **envp, int error_line)
{
	cmd->next = 0;
	cmd->line = NULL;
	cmd->argv = NULL;
	cmd->pid = NULL;
	cmd->redirf = NULL;
	cmd->redirfl = NULL;
	cmd->redirfb = NULL;
	cmdv->envreplace = NULL;
	cmdv->envp = envp;
	cmdv->cp = cmd;
	cmdv->error = 0;
	cmdv->cenvv = 0;
	cmdv->error_line = error_line;
	cmdv->path = NULL;
	cmdv->paths = NULL;
}

void	cmds_loop1(t_cmdv *cmdv)
{
	cmdv->path = get_path(cmdv->envp);
	if (cmdv->path == NULL)
		cmdv->paths = NULL;
	else
	{
		cmdv->path = ft_strdup(cmdv->path);
		cmdv->paths = split_path(cmdv->path);
		free(cmdv->path);
	}
}
