/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <pcariou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 11:24:39 by pcariou           #+#    #+#             */
/*   Updated: 2020/10/15 11:27:30 by pcariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void    open_files(t_cmd *cmd)
{
	int i;
	int fd;

	i = -1;
	while (cmd->redirfb[++i])
	{
		if (!cmd->redirfb[i][0])
			error(cmd->argv[0]);
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

void    open_file(t_cmd *cmd)
{
	if (cmd->redir == '>')
		cmd->fdredir = open(cmd->redirf, O_TRUNC | O_WRONLY | O_CREAT, S_IRWXU);
	else if (cmd->redir == '}')
		cmd->fdredir = open(cmd->redirf, O_APPEND | O_WRONLY | O_CREAT, S_IRWXU);
	else if (cmd->redir == '<')
		cmd->fdredir = open(cmd->redirf, O_RDONLY);
	if (cmd->fdredir == -1)
		return ;
	if (cmd->redir == '>' || cmd->redir == '}')
		dup2(cmd->fdredir, 1);
	else
		dup2(cmd->fdredir, 0);
}

void    create_file(t_cmd *cmd)
{
	if (cmd->nredir > 1)
		open_files(cmd);
	if (!cmd->redirf[0])
		error(cmd->argv[0]);
	else
	{
		cmd->fdredir = open(cmd->redirf, O_TRUNC | O_WRONLY | O_CREAT, S_IRWXU);
		if (cmd->fdredir == -1)
			return ;
		else
			close(cmd->fdredir);
	}
}
