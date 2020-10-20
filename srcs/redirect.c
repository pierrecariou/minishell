/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <pcariou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 11:24:39 by pcariou           #+#    #+#             */
/*   Updated: 2020/10/20 14:57:53 by pcariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void    open_files(t_cmd *cmd, t_cmdv *cmdv)
{
	int i;
	int fd;

	i = -1;
	while (cmd->redirfb[++i])
	{
		if (!cmd->redirfb[i][0])
			error(cmd, cmdv);
		else
		{
			fd = open(cmd->redirfb[i], O_TRUNC | O_WRONLY | O_CREAT, S_IRWXU);
			if (fd == -1)
				return ;
			else
				close(fd);
			fd = 0;
		}
	}
}

int    open_file(t_cmd *cmd)
{
	if (cmd->redir == '>')
		cmd->fdredir = open(cmd->redirf, O_TRUNC | O_WRONLY | O_CREAT, S_IRWXU);
	else if (cmd->redir == '}')
		cmd->fdredir = open(cmd->redirf, O_APPEND | O_WRONLY | O_CREAT, S_IRWXU);
	else if (cmd->redir == '<')
		cmd->fdredir = open(cmd->redirf, O_RDONLY);
	if (cmd->fdredir == -1)
		return (0);
	if (cmd->redir == '>' || cmd->redir == '}')
		dup2(cmd->fdredir, 1);
	else
		dup2(cmd->fdredir, 0);
	return (1);
}

void    create_file(t_cmd *cmd, t_cmdv *cmdv)
{
	if (cmd->nredir > 1)
		open_files(cmd, cmdv);
	if (!cmd->redirf[0])
		error(cmd, cmdv);
	else
	{
		cmd->fdredir = open(cmd->redirf, O_TRUNC | O_WRONLY | O_CREAT, S_IRWXU);
		if (cmd->fdredir == -1)
			return ;
		else
			close(cmd->fdredir);
	}
}
