/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <pcariou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 09:33:06 by pcariou           #+#    #+#             */
/*   Updated: 2020/11/17 16:37:48 by pcariou          ###   ########.fr       */
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

char	*create_space(void)
{
	char *space;

	if (!(space = malloc(2)))
		return (NULL);
	space[0] = ' ';
	space[1] = 0;
	return (space);
}

char	*return_code(char *envv, t_cmdv *cmdv)
{
	char *space;

	if (envv[0] && envv[0] == '?' && !envv[1])
	{
		if (cmdv->code)
		{
			space = ft_itoa(130);
			cmdv->code = 0;
		}
		else
			space = ft_itoa(cmdv->error_line);
		return (space);
	}
	return (NULL);
}
