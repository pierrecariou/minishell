/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <pcariou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 12:28:23 by pcariou           #+#    #+#             */
/*   Updated: 2020/11/17 16:36:02 by pcariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char	*real_env(char *envv, t_cmdv *cmdv)
{
	int		i;
	int		m;
	char	*space;

	i = -1;
	cmdv->renv = 0;
	if ((space = return_code(envv, cmdv)) != NULL)
		return (space);
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
	space = create_space();
	return (space);
}

char	*buf_with_envv(int r, t_cmd *cmd, t_cmdv *cmdv)
{
	int		i;
	int		m;
	int		k;
	char	*ret;

	i = -1;
	m = 0;
	k = 0;
	if (!(ret = malloc(sizeof(char) * (ft_strlen(cmd->argv[r]) +
						(ft_strlen(cmdv->renvv) - (cmdv->length - 1)) + 1))))
		return (0);
	while (++i < cmdv->l)
		ret[m++] = cmd->argv[r][i];
	while (cmdv->renvv[k])
		ret[m++] = cmdv->renvv[k++];
	k = -1;
	while (cmdv->end[++k])
		ret[m++] = cmdv->end[k];
	ret[m] = 0;
	free(cmd->argv[r]);
	return (ret);
}

int		get_envv1(t_cmd *cmd, t_cmdv *cmdv, int i, int k)
{
	int m;

	m = 0;
	while (cmd->argv[k][i] && cmd->argv[k][i] != '/' && cmd->argv[k][i] != '$')
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

	if (cmd->argv[k][i] == '$' && cmd->argv[k][i + 1]
		&& cmdv->envreplace[cmdv->cenvv])
	{
		cmdv->cenvv++;
		m = 0;
		cmdv->l = i;
		cp = ++i;
		while (cmd->argv[k][i] && cmd->argv[k][i] != '/'
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
		cmdv->cenvv++;
}

void	replace_envv(t_cmd *cmd, t_cmdv *cmdv)
{
	int i;
	int k;

	i = -1;
	while (cmd->argv[++i])
	{
		k = -1;
		while (cmd->argv[i][++k])
			get_envv(cmd, cmdv, k, i);
	}
}
