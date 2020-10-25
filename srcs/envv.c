/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <pcariou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 12:28:23 by pcariou           #+#    #+#             */
/*   Updated: 2020/10/25 18:00:59 by pcariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char    *real_env(char *envv, t_cmdv *cmdv)
{
	int i;
	int m;
	char *space;

	i = -1;
	if (envv[0] && envv[0] == '?' && !envv[1])
	{
		space = ft_itoa(cmdv->error_line);
		return (space);
	}
	while (cmdv->envp[++i])
	{
		m = 0;
		while (envv[m] && cmdv->envp[i][m] && envv[m] == cmdv->envp[i][m])
			m++;
		if (!envv[m] && cmdv->envp[i][m] && cmdv->envp[i][m] == '=' && cmdv->envp[i][m + 1])
			return (&cmdv->envp[i][m + 1]);
	}
	space = malloc(2);
	space[0] = ' ';
	space[1] = 0;
	return (space);
}

char    *buf_with_envv(char *buf, char *renvv, char *end, int length, int l)
{
	int i;
	int m;
	int k;
	char *ret;

	i = -1;
	m = 0;
	k = 0;
	if (!(ret = malloc(sizeof(char) * (ft_strlen(buf) + (ft_strlen(renvv) - (length - 1)) + 1))))
		return (0);
	while (++i < l)
		ret[m++] = buf[i];
	while (renvv[k])
		ret[m++] = renvv[k++];
	k = -1;
	while (end[++k])
		ret[m++] = end[k];
	ret[m] = 0;
	//      free(buf);
	return (ret);
}

char    *get_envv(char *buf, t_cmdv *cmdv, int i)
{
	char *envv;
	char *end;
	char *renvv;
	int cp;
	int m;
	int length;
	//int r;
	int l;

	while (buf[++i])
	{
		if (buf[i] == '$' && buf[i + 1] && cmdv->envreplace[cmdv->cenvv] == 1)
		{
			cmdv->cenvv++;
			m = 0;
			l = i;
			cp = ++i;
			while (buf[i] && buf[i] != '/' && buf[i] != '$')
			{
				m++;
				i++;
			}
			if (!(envv = malloc(sizeof(char) * m + 1)))
				return (0);
			i = cp;
			m = 0;
			while (buf[i] && buf[i] != '/' && buf[i] != '$')
				envv[m++] = buf[i++];
			envv[m] = 0;
			//              r = i;
			end = &buf[i];
			length = ft_strlen(envv);
			renvv = real_env(envv, cmdv);
			//printf("%s\n", renvv);
			buf = buf_with_envv(buf, renvv, end, length, l);
			//free(renvv);
			free(envv);
			get_envv(buf, cmdv, i - 1);
		}
		else if (buf[i] == '$')
			cmdv->cenvv++;
	}
	return (buf);
}

void    replace_envv(t_cmd *cmd, t_cmdv *cmdv)
{
	int i;

	i = -1;
	while (cmd->argv[++i])
		cmd->argv[i] = get_envv(cmd->argv[i], cmdv, -1);
}
