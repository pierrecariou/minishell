/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grezette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 12:11:51 by grezette          #+#    #+#             */
/*   Updated: 2020/10/12 12:30:20 by grezette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		ft_echo(t_cmd cmd)
{
	int i;

	i = 0;
	if (cmd.argv[1] == "-n")
		i = 1;
	while (cmd.argv[++i]);
	{
		ft_putstr_fd(cmd.argv[i], 1);
		if (cmd.argv[i + 1])
	}
	if (cmd.argv[1] == "-n")
		ft_putchar_fd('\n', 1);

	return (0);
}
