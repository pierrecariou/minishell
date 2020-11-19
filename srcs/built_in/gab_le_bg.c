/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gab_le_bg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grezette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 18:19:20 by grezette          #+#    #+#             */
/*   Updated: 2020/11/04 22:40:47 by pcariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**ft_square_free(char **tab)
{
	int i;

	i = 0;
	while (tab && tab[i])
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
	return (NULL);
}

char	**ft_square_strjoin(char **tab, char *str)
{
	char	**ret;
	int		i;

	i = 0;
	while (tab && tab[i])
		i++;
	if (!(ret = (char **)malloc(sizeof(char *) * (i + 2))))
		return (NULL);
	i = -1;
	while (tab && tab[++i])
		if (!(ret[i] = ft_strdup(tab[i])))
			return (ft_square_free(ret));
	i = (str) ? i : i - 1;
	i = (i < 0) ? 0 : i;
	if (str)
		if (!(ret[i] = ft_strdup(str)))
			return (ft_square_free(ret));
	ret[i + 1] = NULL;
	return (ret);
}

size_t	ft_square_strlen(char **str)
{
	int i;

	i = 0;
	if (str)
		while (str[i])
			i++;
	return (i);
}
