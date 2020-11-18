/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <pcariou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 12:33:58 by pcariou           #+#    #+#             */
/*   Updated: 2020/11/18 15:02:10 by pcariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_alpha_error(char *argv)
{
	write(2, "minishell: exit: ", 17);
	write(2, argv, ft_strlen(argv));
	write(2, ": numeric argument required\n", 28);
	return (255);
}

static int	ft_cal_output(char *argv)
{
	unsigned long long	ret;
	int					i;
	int 				minus;

	ret = 0;
	i = argv[0] == '-' || argv[0] == '+' ? 0 : -1;
	minus = argv[0] == '-' ? 1 : 0;
	while (argv[++i])
	{
		if (ret >= 922337203685477580 && argv[i] > '7')
			return (ft_alpha_error(argv));
		ret *= 10;
		ret += (argv[i] - '0');
	}
	ret = minus ? 256 - ret % 256 : ret % 256;
	ret = ret == 256 ? 0 : ret;
	return (ret);
}

static int	ft_grezette_exit(t_cmd cmd, t_cmdv *cmdv)
{
	int i;

	if (!cmd.argv[1])
		return (cmdv->error_line);
	i = cmd.argv[1][0] == '-' || cmd.argv[1][0] == '+' ? 1 : 0;
	while (cmd.argv[1][i] && ft_isdigit(cmd.argv[1][i]))
		i++;
	if (i != ft_strlen(cmd.argv[1]))
		return (ft_alpha_error(cmd.argv[1]));
	else if (ft_square_strlen(cmd.argv) > 2)
	{
		write(2, "minishell: exit: too many arguments\n", 37);
		return (257);
	}
	else
		return (ft_cal_output(cmd.argv[1]));
}

int	ft_exit(t_cmd cmd, t_cmdv *cmdv, char *file, char **paths)
{
	int	i;

	ft_putstr_fd("exit\n", 0);
	i = ft_grezette_exit(cmd ,cmdv);
	if (i == 257)
		return (1);
	free_paths(paths, cmdv->envp, 0);
	free_structs(cmdv);
	free(file);
	exit(i);
	return (i);
}
