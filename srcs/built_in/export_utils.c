/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grezette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 18:19:20 by grezette          #+#    #+#             */
/*   Updated: 2020/11/23 10:45:00 by pcariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*ft_my_strjoin(char const *str1, char const *str2)
{
	char	*join;
	char	*s1;
	char	*s2;
	size_t	size;

	size = 1;
	s1 = (char *)str1;
	s2 = (char *)str2;
	if (s1)
		size = ft_strlen(s1) + 1;
	if (s2)
		size += ft_strlen(s2);
	if (!(join = (char *)malloc(sizeof(*join) * size)))
		return (NULL);
	if (s1)
		ft_memcpy(join, s1, ft_strlen(s1));
	if (s2)
		ft_memcpy(&join[size - ft_strlen(s2) - 1], s2, ft_strlen(s2));
	join[size - 1] = 0;
	ft_putstr_fd(join, 1);
	return (join);
}

int			ft_modif_var(char *a, t_cmdv *cmdv, int i, int j)
{
	char *tmp;

	tmp = cmdv->envp[j];
	if (a[i] == '+')
	{
		if (!cmdv->envp[j][i])
		{
			if (!(cmdv->envp[j] = ft_my_strjoin(cmdv->envp[j], &a[i + 1])))
				return (-1);
		}
		else
			if (!(cmdv->envp[j] = ft_my_strjoin(cmdv->envp[j], &a[i + 2])))
				return (-1);
	}
	else if (!a[i] && cmdv->envp[j][i] == '=')
		return (0);
	else
		if (!(cmdv->envp[j] = ft_strdup(a)))
			return (-1);
	free(tmp);
	return (0);
}

int			ft_create_new_var(char *a, t_cmdv *cmdv, int i)
{
	char **tmp;

	tmp = cmdv->envp;
	if (a[i] == '+')
		while (a[(++i) - 1])
			a[i - 1] = a[i];
	if (!(tmp = ft_square_strjoin(tmp, a)))
		return (-1);
	ft_square_free(cmdv->envp);
	cmdv->envp = tmp;
	return (-1);
}
