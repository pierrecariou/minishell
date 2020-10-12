/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <pcariou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 16:32:57 by pcariou           #+#    #+#             */
/*   Updated: 2020/10/12 16:33:58 by pcariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int     double_sep(char *buf)
{
	int i;

	i = -1;
	while (buf[++i])
	{
		if ((buf[i] == '|' || buf[i] == ';') &&
				(buf[i + 1] && (buf[i+1] == '|' ||
								buf[i+1] == ';')))
			return (1);
	}
	return (0);
}

int             bad_beginning(char *buf)
{
	int i;

	i = 0;
	while (ft_isspace(buf[i]))
		i++;
	if (buf[i] == '|' || buf[i] == ';')
		return (1);
	return (0);
}
