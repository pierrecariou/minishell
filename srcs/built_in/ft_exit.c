/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <pcariou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 12:33:58 by pcariou           #+#    #+#             */
/*   Updated: 2020/11/17 15:04:24 by pcariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_exit(char **envp, t_cmdv *cmdv, char *file, char **paths)
{
	free_paths(paths, envp, 0);
	free_structs(cmdv);
	free(file);
	ft_putstr_fd("exit\n", 0);
	exit(0);
}
