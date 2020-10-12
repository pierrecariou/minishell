/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grezette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 16:18:47 by grezette          #+#    #+#             */
/*   Updated: 2020/10/12 16:34:38 by grezette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		ft_pwd(t_cmd cmd)
{
	char	*src;
	int		fctr;

	(void)cmd;
	fctr = 1;
	if (!(src = (char *)malloc(sizeof(char *) * (fctr + 1))))
		return (-1);
	while (!(getcwd(scr, fctr)))
	{
		free(scr);
		if (!(src = (char *)malloc(sizeof(char *) * (++fctr + 1))))
			return (-1);
	}
	ft_putstr_fd(scr, 1);
	free(scr);
	return (0);
}
