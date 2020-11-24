/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grezette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 18:19:20 by grezette          #+#    #+#             */
/*   Updated: 2020/11/24 16:04:15 by pcariou          ###   ########.fr       */
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

static int	ft_unset_one_var(char *arg, t_cmdv *cmdv)
{
	int i;

	i = -1;
	while (arg[++i])
		if ((!ft_isalpha(arg[i]) && arg[i] != '_') || ft_isdigit(arg[0]))
			return (-1);
	while (cmdv->envp[++i])
	{
		if (!ft_strncmp(arg, cmdv->envp[i], ft_strlen(arg)) &&
				(cmdv->envp[i][ft_strlen(arg)] == '=' ||
				!cmdv->envp[i][ft_strlen(arg)]))
		{
			free(cmdv->envp[i]);
			cmdv->envp[i] = cmdv->envp[i + 1];
			while (cmdv->envp[++i])
				cmdv->envp[i] = cmdv->envp[i + 1];
			break ;
		}
	}
	return (0);
}

void		ft_unset(t_cmd cmd, t_cmdv *cmdv)
{
	int i;

	i = 0;
	while (cmd.argv[++i])
		if (ft_unset_one_var(cmd.argv[i], cmdv))
		{
			cmdv->err_built = 1;
			write(2, "minishell: unset: `", 19);
			write(2, cmd.argv[i], ft_strlen(cmd.argv[i]));
			write(2, "': not a valid identifier\n", 27);
		}
}
