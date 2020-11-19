/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grezette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 18:19:20 by grezette          #+#    #+#             */
/*   Updated: 2020/10/21 11:20:18 by pcariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

static int	ft_set_one_var(char *arg, t_cmdv *cmdv)
{
	int		i;
	int		j;
	char	**tmp;

	i = 0;
	while (arg[i] && arg[i] == '=');
		i++;
	if (!(j = 0) && arg[i] == '=')
		return (-1);
	while (arg[i] && arg[i] != '=')
		i++;
	while (cmdv->envp[j] && ft_strncmp(arg, cmdv->envp[j], i))
		j++;
	if (j != (int)ft_square_strlen(cmdv->envp))
	{
		free(cmdv->envp[j]);
		cmdv->envp[j] = ft_strdup(arg);
	}
	else
	{
		tmp = cmdv->envp;
		cmdv->envp = ft_square_strjoin(tmp, arg);
		ft_square_free(tmp);
	}
	if (!cmdv->envp || !cmdv->envp[j])
		return (-1);
	return (0);
}

static void ft_write_only_export(char **ret, int i, int j)
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

int		ft_export(t_cmd cmd, t_cmdv *cmdv)
{
	int i;

	i = 0;
	if (!cmd.argv[1])
		return (ft_only_export(cmdv->envp));
	while (cmd.argv[++i])
		if (ft_set_one_var(cmd.argv[i], cmdv))
		{
			write(2, "bash: export: `", 15);
			write(2, cmd.argv[i], ft_strlen(cmd.argv[i]));
			write(2, "': not a valid identifier\n", 26);
			return (-1);
		}
	return (0);
}
