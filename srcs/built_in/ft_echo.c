/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grezette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 12:11:51 by grezette          #+#    #+#             */
/*   Updated: 2020/11/06 19:45:14 by pcariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		ft_echo(t_cmd cmd)
{
	int i;

	i = 0;
	if (!cmd.argv[1])
		write(1, "\n", 1);
	if (!ft_strcmp(cmd.argv[1], "-n"))
		i = 1;
	while (cmd.argv[++i])
	{
		ft_putstr_fd(cmd.argv[i], 1);
		if (cmd.argv[i + 1])
			write(1, " ", 1);
	}
	if (cmd.argv[1] && ft_strcmp(cmd.argv[1], "-n"))
	  write(1, "\n", 1);
	return (0);
}
