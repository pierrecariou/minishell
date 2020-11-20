/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <pcariou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 12:28:23 by pcariou           #+#    #+#             */
/*   Updated: 2020/11/20 11:50:16 by pcariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char	*real_env(char *envv, t_cmdv *cmdv)
{
	int		i;
	int		m;

	i = -1;
	cmdv->renv = 0;
	while (cmdv->envp[++i])
	{
		m = 0;
		while (envv[m] && cmdv->envp[i][m] && envv[m] == cmdv->envp[i][m])
			m++;
		if (!envv[m] && cmdv->envp[i][m] && cmdv->envp[i][m] == '='
				&& cmdv->envp[i][m + 1])
		{
			cmdv->renv = 1;
			return (&cmdv->envp[i][m + 1]);
		}
	}
	cmdv->noenvv = 1;
	return (NULL);
}

char	*buf_with_envv(int r, t_cmd *cmd, t_cmdv *cmdv)
{
	int		i;
	int		m;
	char	*ret;

	i = -1;
	m = 0;
	if (!(ret = malloc(sizeof(char) * (ft_strlen(cmd->argv[r]) +
						(ft_strlen(cmdv->renvv) - (cmdv->length - 1)) + 1))))
		return (0);
	while (++i < cmdv->l)
		ret[m++] = cmd->argv[r][i];
	i = 0;
	while (cmdv->renvv != NULL && cmdv->renvv[i])
		ret[m++] = cmdv->renvv[i++];
	i = -1;
	while (cmdv->end[++i])
		ret[m++] = cmdv->end[i];
	ret[m] = 0;
	if (m == 0)
	{
		free(ret);
		ret = NULL;
	}
	free(cmd->argv[r]);
	return (ret);
}

int		get_envv1(t_cmd *cmd, t_cmdv *cmdv, int i, int k)
{
	int m;

	m = 0;
	while (cmd->argv[k][i] && ft_isenvv(cmd->argv[k][i]) &&
			cmd->argv[k][i] != '$')
		cmdv->envv[m++] = cmd->argv[k][i++];
	cmdv->envv[m] = 0;
	cmdv->end = &cmd->argv[k][i];
	cmdv->length = ft_strlen(cmdv->envv);
	cmdv->renvv = real_env(cmdv->envv, cmdv);
	cmd->argv[k] = buf_with_envv(k, cmd, cmdv);
	if (!cmdv->renv)
		free(cmdv->renvv);
	free(cmdv->envv);
	return (i);
}

void	get_envv(t_cmd *cmd, t_cmdv *cmdv, int i, int k)
{
	int		cp;
	int		m;

	if (cmd->argv[k][i] == '$' && cmd->argv[k][i + 1] &&
			ft_isenvv(cmd->argv[k][i + 1]) && cmdv->envreplace[cmdv->cenvv])
	{
		cmdv->cenvv++;
		m = 0;
		cmdv->l = i;
		cp = ++i;
		while (cmd->argv[k][i] && ft_isenvv(cmd->argv[k][i])
				&& cmd->argv[k][i] != '$')
		{
			m++;
			i++;
		}
		if (!(cmdv->envv = malloc(sizeof(char) * m + 1)))
			return ;
		i = get_envv1(cmd, cmdv, cp, k);
	}
	else if (cmd->argv[k][i] && cmd->argv[k][i] == '$')
		code(cmd, cmdv, i, k);
}

void	replace_envv(t_cmd *cmd, t_cmdv *cmdv)
{
	int i;
	int k;

	i = -1;
	while (cmd->argv[++i])
	{
		k = -1;
		while (cmd->argv[i] != NULL && cmd->argv[i][++k])
		{
			cmdv->noenvv = 0;
			get_envv(cmd, cmdv, k, i);
			if (cmdv->noenvv)
				k--;
		}
		if (cmd->argv[i] == NULL)
			argv_reborn(cmd, i--);
	}
}
