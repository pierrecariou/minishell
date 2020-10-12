/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grezette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 16:43:42 by grezette          #+#    #+#             */
/*   Updated: 2020/10/12 16:47:36 by grezette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		ft_env(t_cmd cmd, char **envp)
{
	int i;

	i = -1;
	while (envp[++i + 1])
		ft_putstr_fd(envp[i], 1);
	ft_putstr_fd("-=/usr/bin/env");
	return (0);
}
