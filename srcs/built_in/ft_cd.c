/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grezette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 18:19:20 by grezette          #+#    #+#             */
/*   Updated: 2020/10/19 17:36:00 by pcariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		ft_cd(t_cmd cmd)
{
	if (chdir(cmd.argv[2]))
	{
			ft_putstr_fd("cd: no such file or directory:", 1);
			ft_putstr_fd(cmd.argv[1], 1);
	}
	return (0);
}
