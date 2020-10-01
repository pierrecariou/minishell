/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <pcariou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 10:53:46 by pcariou           #+#    #+#             */
/*   Updated: 2020/10/01 17:07:25 by pcariou          ###   ########.fr       */
/*                                                                            */
/* **************************************************************************/

#include "minishell.h"

/*
void	handler(int num) 
{
	(void)num;
	write(1, "handling!\n", 10);
}
*/

void	check_echo(char *buf)
{
	ft_putstr_fd(buf, 1);	
}

void	check_input(char *buf)
{
	if (ft_strcmp(buf, "echo") == 0)
		check_echo(buf);
	else
	{
		ft_putstr_fd("command not found: ", 1);
		ft_putstr_fd(buf, 1);
	}
	ft_putstr_fd("\n", 1);
}

void	better_input(char *buf)
{
	int i;

	i = 0;
	while (buf[i] > 31 && buf[i] < 127)
		i++;
	buf[i] = 0;
}

void	read_input(void)
{
	char buf[300];

	read(0, buf, 300);
	better_input(buf);
	check_input(buf);
}

void	loop(void)
{
	while (42)
	{
		ft_putstr_fd("\033[1;31m", 1);
		ft_putstr_fd("minishell> ", 1);
		ft_putstr_fd("\033[0m", 1);
		read_input();
	}
}

int		main(void)
{
	//signal(SIGINT, handler);
	loop();
	return (0);
}
