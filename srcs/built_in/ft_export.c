/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grezette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 18:19:20 by grezette          #+#    #+#             */
/*   Updated: 2020/10/20 15:16:36 by pcariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_strncmp(char *s1, char *s2, size_t n)
{
	size_t i;

	i = 0;
	if (n == 0)
		return (0);
	while (i < n - 1 && s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

static int		ft_set_one_var(char *arg, t_cmdv *cmdv)
{
	int i;
	int j;
	char **tmp;

	i = 0;
	j = 0;
	while (arg[i] != '=')
		i++;
	while (cmdv->envp[j] && ft_strncmp(arg, cmdv->envp[j], i - 1))
		j++;
	if (j != (int)ft_square_strlen(cmdv->envp))
	{
		free(cmdv->envp[j]);
		if (!(cmdv->envp[j] = ft_strdup(arg)))
			return (-1);
	}
	else
	{
		tmp = cmdv->envp;
		if (!(cmdv->envp = ft_square_strjoin(tmp, arg)))
			return (-1);
		ft_square_free(tmp);
	}
	return (0);
}

int		ft_export(t_cmd cmd, t_cmdv *cmdv)
{
	int i;

	i = 0;
	while (cmd.argv[++i])
		if (ft_set_one_var(cmd.argv[i], cmdv))
			return (-1);
	return (0);
}
