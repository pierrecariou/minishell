/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grezette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 16:18:47 by grezette          #+#    #+#             */
/*   Updated: 2020/10/19 11:11:17 by grezette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		ft_pwd(t_cmd cmd, t_cmdv *cmdv)
{
	char	*src;
	int		fctr;

	if (cmd.argv[1])
	{
		ft_putstr_fd("minishell: pwd: too many arguments", 2);
		return (-1);
	}
	fctr = 4096;
	if (!(src = (char *)malloc(sizeof(char *) * (fctr))))
		return (-1);
	while (!(getcwd(src, fctr)))
	{
		free(src);
		fctr *= 2;
		if (!(src = (char *)malloc(sizeof(char *) * (fctr))))
			return (-1);
	}
	ft_putstr_fd(src, 1);
	free(src);
	write(1, "\n", 1);
	return (0);
}
