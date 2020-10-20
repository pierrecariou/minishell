/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmp_built_in.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grezette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 15:01:30 by grezette          #+#    #+#             */
/*   Updated: 2020/10/20 11:34:30 by pcariou          ###   ########.fr       */
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
		ft_pwd(*cmd);
	else if (!ft_strcmp(argv[0], "env"))
		ft_env(*cmd, cmdv->envp);
	else if (!ft_strcmp(argv[0], "unset"))
		ft_putstr_fd("A work in progress\n", 1);
	else if (!ft_strcmp(argv[0], "export"))
		ft_putstr_fd("A work in progress\n", 1);
	else if (!ft_strcmp(argv[0], "exit"))
		ft_putstr_fd("A work in progress\n", 1);
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
		!ft_strcmp(argv[1], "exit"))
		exe = 1;
	else
		exe = 0;
	return (exe);
}
