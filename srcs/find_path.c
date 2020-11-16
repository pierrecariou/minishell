/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <pcariou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 12:02:27 by pcariou           #+#    #+#             */
/*   Updated: 2020/11/16 11:42:13 by pcariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int		not_a_path(char *word)
{
	int i;

	i = ft_strlen(word);
	while (--i >= 0)
	{
		if (word[i] == '/')
			return (0);
	}
	return (1);
}

char	*file_stat(char *file)
{
	struct stat buf;

	if (stat(file, &buf) == 0)
		return (ft_strdup(file));
	return (NULL);
}

char	*concat_path_exec(char *path, char *exec)
{
	char	*ret;
	int		i;
	int		k;

	i = -1;
	k = 0;
	if (!(ret = malloc(sizeof(char) * (ft_strlen(path) + ft_strlen(exec) + 2))))
		return (0);
	while (path[++i])
		ret[k++] = path[i];
	ret[k++] = '/';
	i = -1;
	while (exec[++i])
		ret[k++] = exec[i];
	ret[k] = 0;
	return (ret);
}

char	*exec_path(char **paths, char *exec)
{
	int				i;
	struct stat		buf;
	char			*file;

	i = -1;
	if (!paths)
		return (NULL);
	while (paths[++i])
	{
		file = concat_path_exec(paths[i], exec);
		if (stat(file, &buf) == 0)
			return (file);
		else
			free(file);
	}
	return (NULL);
}
