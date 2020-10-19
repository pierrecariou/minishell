/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmp_built_in.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grezette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 15:01:30 by grezette          #+#    #+#             */
/*   Updated: 2020/10/19 15:06:20 by grezette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		cmp_built_in(char **argv, t_cmd *cmd, t_cmdv *cmdv)
{
	int exe;

	exe = 1;
	if (ft_strncmp(argv[0], "echo", 4))
		ft_echo(*cmd);
	else if (ft_strncmp(argv[0], "cd", 2))
		ft_cd(*cmd);
	else if (ft_strncmp(argv[0], "pwd", 3))
		ft_pwd(*cmd);
	else if (ft_strncmp(argv[0], "env", 2))
		ft_env(*cmd, cmdv->envp);
	else if (ft_strncmp(argv[0], "unset", 2))
		ft_putstr_fd("A work in progress\n", 1);
	else if (ft_strncmp(argv[0], "export", 2))
		ft_putstr_fd("A work in progress\n", 1);
	else if (ft_strncmp(argv[0], "exit", 2))
		ft_putstr_fd("A work in progress\n", 1);
	else
		exe = 0;
	return (exe);
}
