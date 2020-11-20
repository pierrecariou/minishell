/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <pcariou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 09:33:06 by pcariou           #+#    #+#             */
/*   Updated: 2020/11/20 11:51:35 by pcariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	pipe_fd_fill(t_cmd *cmd)
{
	int fd[2];

	while (cmd->sep == '|' && cmd->next)
	{
		pipe(fd);
		cmd->fdout = fd[1];
		cmd->next->fdin = fd[0];
		cmd = cmd->next;
	}
}

void	code(t_cmd *cmd, t_cmdv *cmdv, int i, int k)
{
	if ((cmdv->renvv = return_code(cmd, cmdv, k, i)) != NULL)
	{
		cmd->argv[k] = buf_with_envv(k, cmd, cmdv);
		free(cmdv->renvv);
	}
	cmdv->cenvv++;
}

char	*return_code(t_cmd *cmd, t_cmdv *cmdv, int k, int i)
{
	char *ret;

	if (cmd->argv[k][i + 1] && cmd->argv[k][i + 1] == '?')
	{
		if (cmdv->code)
		{
			ret = ft_itoa(130);
			cmdv->code = 0;
		}
		else
			ret = ft_itoa(cmdv->error_line);
		cmdv->l = i;
		cmdv->length = 2;
		cmdv->end = &cmd->argv[k][i + 2];
		return (ret);
	}
	return (NULL);
}

void	argv_reborn(t_cmd *cmd, int i)
{
	int k;

	while (cmd->argv[i + 1])
	{
		k = 0;
		if (!(cmd->argv[i] = malloc(sizeof(char) *
						(ft_strlen(cmd->argv[i + 1]) + 1))))
			return ;
		while (cmd->argv[i + 1][k])
		{
			cmd->argv[i][k] = cmd->argv[i + 1][k];
			k++;
		}
		cmd->argv[i][k] = 0;
		free(cmd->argv[i + 1]);
		i++;
	}
	cmd->argv[i] = 0;
}
