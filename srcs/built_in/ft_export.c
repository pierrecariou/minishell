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
#include <stdio.h>

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
	return (join);
}

static int	ft_strncmp(char *s1, char *s2, size_t n)
{
	size_t i;

	i = 0;
	if (n == 0)
		return (0);
	while (i < n - 1 && s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

static int	ft_modif_var(char *a, t_cmdv *cmdv, int i, int j)
{
	char *tmp;

	tmp = cmdv->envp[j];
	if (a[i] == '+')
	{
		if (!cmdv->envp[j][i] &&
				!(cmdv->envp[j] = ft_my_strjoin(cmdv->envp[j], &a[i + 1])))
			return (-1);
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

static int	ft_create_new_var(char *a, t_cmdv *cmdv, int i)
{
	char **tmp;

	tmp = cmdv->envp;
	if (!(tmp = ft_square_strjoin(tmp, a)))
		return (-1);
	ft_square_free(cmdv->envp);
	cmdv->envp = tmp;
	if (a[i] == '+')
		while (a[++i])
			a[i] = a[i + 1];
	return (-1);
}

static int	ft_set_one_var(char *a, t_cmdv *cmdv)
{
	int		i;
	int		j;

	i = -1;
	j = -1;
	while (a[++i] && (a[i] != '=' || a[0] == '=') &&
			(a[i] != '+' || a[i + 1] != '='))
		if (a[i] == ' ' || a[0] == '=' || (!ft_isalnum(a[i]) && a[i] != '_'))
			return (-1);
	while (cmdv->envp[++j])
		if (!ft_strncmp(a, cmdv->envp[j], i) &&
				(cmdv->envp[j][i] == '=' || cmdv->envp[j][i] == 0))
				break ;
	if (j != (int)ft_square_strlen(cmdv->envp))
		ft_modif_var(a, cmdv, i, j);
	else
		ft_create_new_var(a, cmdv, i);
	return (0);
}

static void	ft_write_only_export(char **ret, int i, int j)
{
	write(1, "declare -x ", 11);
	while (ret[i][j] && ret[i][j] != '=')
		j++;
	write(1, ret[i], j + 1);
	if (j != ft_strlen(ret[i]))
	{
		write(1, "\"", 1);
		write(1, &ret[i][j + 1], ft_strlen(ret[i]) - j - 1);
		write(1, "\"", 1);
	}
	write(1, "\n", 1);
}

static int	ft_only_export(char **envp)
{
	char	**ret;
	char	*tmp;
	int		i;
	int		j;

	i = -1;
	if (!(ret = ft_square_strjoin(envp, NULL)))
		return (-1);
	while (ret[++i] && (j = -1))
		while (ret[++j + 1])
			if (ft_strcmp(ret[j], ret[j + 1]) > 0)
			{
				tmp = ret[j];
				ret[j] = ret[j + 1];
				ret[j + 1] = tmp;
			}
	i = -1;
	while (ret[++i])
		ft_write_only_export(ret, i, 0);
	ft_square_free(ret);
	return (0);
}

int			ft_export(t_cmd cmd, t_cmdv *cmdv)
{
	int i;

	i = 0;
	if (!cmd.argv[1])
		return (ft_only_export(cmdv->envp));
	while (cmd.argv[++i])
		if (ft_set_one_var(cmd.argv[i], cmdv))
		{
			cmdv->err_built = 1;
			ft_putstr_fd("minishell: export: `", 2);
			write(2, cmd.argv[i], ft_strlen(cmd.argv[i]));
			write(2, "': not a valid identifier\n", 26);
			return (-1);
		}
	return (0);
}
