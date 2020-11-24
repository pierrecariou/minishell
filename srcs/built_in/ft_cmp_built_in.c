/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmp_built_in.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grezette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 15:01:30 by grezette          #+#    #+#             */
/*   Updated: 2020/11/23 09:38:21 by pcariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		cmp_built_in(char **argv, t_cmd *cmd, t_cmdv *cmdv)
{
	int exe;

	exe = 1;
	if (!ft_strcmp(argv[0], "echo"))
		ft_echo(*cmd);
	else if (!ft_strcmp(argv[0], "cd"))
		ft_cd(*cmd, cmdv);
	else if (!ft_strcmp(argv[0], "pwd"))
		ft_pwd(*cmd, cmdv);
	else if (!ft_strcmp(argv[0], "env"))
		ft_env(*cmd, cmdv->envp);
	else if (!ft_strcmp(argv[0], "unset"))
		ft_unset(*cmd, cmdv);
	else if (!ft_strcmp(argv[0], "export"))
		ft_export(*cmd, cmdv);
	else if (!ft_strcmp(argv[0], "exit"))
		exe = 1;
	else
		exe = 0;
	return (exe);
}

int		is_built_in(char **argv)
{
	int exe;

	if (!ft_strcmp(argv[0], "echo") || !ft_strcmp(argv[0], "cd") ||
		!ft_strcmp(argv[0], "pwd") || !ft_strcmp(argv[0], "env") ||
		!ft_strcmp(argv[0], "unset") || !ft_strcmp(argv[0], "export") ||
		!ft_strcmp(argv[0], "exit"))
		exe = 1;
	else
		exe = 0;
	return (exe);
}

int		no_fork(char **argv)
{
	if (!argv[0])
		return (0);
	if (!ft_strcmp(argv[0], "cd") || !ft_strcmp(argv[0], "unset") ||
		(!ft_strcmp(argv[0], "export") && argv[1]) ||
		!ft_strcmp(argv[0], "exit"))
		return (1);
	else
		return (0);
}
