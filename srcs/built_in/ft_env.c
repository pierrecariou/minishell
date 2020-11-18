/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grezette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 16:43:42 by grezette          #+#    #+#             */
/*   Updated: 2020/10/19 12:14:49 by grezette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		ft_env(t_cmd cmd, char **envp)
{
	int i;
	int j;

	if (cmd.argv[1])
		return (-1);
	i = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] && envp[i][j] != '=')
			j++;
		if (j != ft_strlen(envp[i]))
		{
			ft_putstr_fd(envp[i], 1);
			write(1, "\n", 1);
		}
		i++;
	}
	return (0);
}
