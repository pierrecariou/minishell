/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <pcariou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 10:53:46 by pcariou           #+#    #+#             */
/*   Updated: 2020/11/23 11:41:31 by pcariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int		g_handler;
int		g_code;

void	inthandler(int num)
{
	(void)num;
	ft_putstr_fd("\n", 1);
	ft_putstr_fd("\033[1;31m", 0);
	ft_putstr_fd("The-Minishell-Project", 0);
	ft_putstr_fd("\033[0m", 0);
	ft_putstr_fd("$ ", 0);
	g_handler++;
	g_code = 1;
	return ;
}

void	prompt(void)
{
	if (g_handler == 2)
		ft_putstr_fd("\33[2K\r", 0);
	g_handler = 0;
	ft_putstr_fd("\033[1;31m", 0);
	ft_putstr_fd("The-Minishell-Project", 0);
	ft_putstr_fd("\033[0m", 0);
	ft_putstr_fd("$ ", 0);
}

void	cmds_loop(t_cmd *cmd, t_cmdv *cmdv, char **envp)
{
	while (cmd)
	{
		cmdv->code = g_code;
		g_code = 0;
		cmdv->err_built = 0;
		cmds_loop1(cmdv);
		if (cmdv->error_line && cmdv->error_line != 127 &&
			cmdv->error_line != 1 && !cmdv->err_built)
			cmdv->error_line = 2;
		if (cmd->active)
		{
			replace_envv(cmd, cmdv);
			if (!cmd->argv[0] && (cmd->redir == '>' || cmd->redir == '}'))
				create_file(cmd, cmdv);
			if (!cmd->argv[0])
				cmdv->error = 1;
			else
				fork_ps(cmd, cmdv->paths, cmdv, envp);
		}
		if (cmdv->err_built)
			cmdv->error_line = cmdv->err_built;
		cmd = cmd->next;
		free_paths(cmdv->paths, envp, 1);
	}
	g_handler++;
}

void	loop(char **envp)
{
	t_cmd	*cmd;
	t_cmdv	*cmdv;
	int		error_line;
	int		parse;

	error_line = 0;
	while (42)
	{
		prompt();
		if (!(cmd = malloc(sizeof(t_cmd))))
			return ;
		if (!(cmdv = malloc(sizeof(t_cmdv))))
			return ;
		init_loop(cmd, cmdv, envp, error_line);
		if ((parse = read_input(cmd, cmdv, cmdv->paths, envp)))
			cmds_loop(cmd, cmdv, envp);
		else if (!cmdv->empty)
			ft_putstr_fd("minishell: syntax error\n", 2);
		if ((!parse && !cmdv->no_line) || (cmdv->error_line != 0 &&
			cmdv->error_line != 127 && !cmdv->err_built))
			error_line = 2;
		error_line = (parse) ? cmdv->error_line : error_line;
		envp = cmdv->envp;
		free_structs(cmdv);
	}
}

int		main(int argc, char **argv, char **envp)
{
	char **tmp_env;

	(void)argc;
	(void)argv;
	g_handler = 0;
	g_code = 0;
	signal(SIGINT, inthandler);
	signal(SIGQUIT, quithandler);
	tmp_env = ft_square_strjoin(envp, NULL);
	loop(tmp_env);
	return (0);
}
