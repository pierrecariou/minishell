/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <pcariou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 13:50:19 by pcariou           #+#    #+#             */
/*   Updated: 2020/11/06 15:37:17 by pcariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

//i[0] = i = -1
//i[1] = c = -1;
//i[2] = k = 0;
//i[3] = l = 0;
//i[4] = m = -1;

char **split_path(char *path)
{
	char **paths;
	int i[5];

	i[0] = -1;
	i[1] = -1;
	i[2] = 0;
	i[4] = -1;
	while (path[++i[0]])
		i[2] = (path[i[0]] == ':') ? i[2] + 1 : i[2];
	if (!(paths = malloc(sizeof(char *) * (i[2] + 2))))
		return (0);
	paths[i[2] + 1] = 0;
	i[0] = -1;
	while (++i[4] < i[2] + 1)
	{
		while (path[++i[1]] && path[i[1]] != ':')
			i[3] = 0;
		if (!(paths[i[4]] = malloc(sizeof(char) * (i[1] - i[0]))))
			return (0);
		while (path[++i[0]] && path[i[0]] != ':')
			paths[i[4]][i[3]++] = path[i[0]];
		paths[i[4]][i[3]] = 0;
		i[3] = 0;
	}
	return (paths);
}

char    *get_path(char **envp)
{
	int i;

	i = -1;
	while (envp[++i])
	{
		if (envp[i][0] == 'P' && envp[i][1] == 'A'
				&& envp[i][2] == 'T' && envp[i][3] == 'H'
				&& envp[i][4] == '=')
			return (&envp[i][5]);
	}
	return (0);
}

