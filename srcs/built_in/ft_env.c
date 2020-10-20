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

	(void)cmd;
	i = -1;
	while (envp[++i + 1])
	{
		ft_putstr_fd(envp[i], 1);
		write(1, "\n", 1);
	}
	ft_putstr_fd("_=/usr/bin/env", 1);
	write(1, "\n", 1);
	return (0);
}
