/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <pcariou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 10:53:46 by pcariou           #+#    #+#             */
/*   Updated: 2020/10/15 11:29:02 by pcariou          ###   ########.fr       */
/*                                                                            */
/* **************************************************************************/

#include "includes/minishell.h"

/*
   void	handler(int num) 
   {
   (void)num;
   write(1, "handling!\n", 10);
   }
 */

void	error(char *buf)
{
	if (buf[0])
	{
		ft_putstr_fd("command not found: ", 1);
		ft_putstr_fd(buf, 1);
		ft_putstr_fd("\n", 1);
	}
	else
		ft_putstr_fd("error\n", 2);
}

void		exec_built(char *file, char **argv, t_cmd *cmd)
{
	//if (strcmp(argv[0], "echo") || ...)
	// built_in();
	//else
	if (cmd->nredir > 1)
		open_files(cmd);
	if (cmd->redir)
		open_file(cmd);
	execve(file, argv, NULL);
	if (cmd->redir)
		close(cmd->fdredir);
}

void	list(t_cmd *cmd, char *file, t_cmdv *cmdv)
{
	int pid;

	pipe_fd_reset(cmdv->cp);
	if ((pid = fork()) == 0)
		exec_built(file, cmd->argv, cmd);
	waitpid(pid, NULL, 0);
}

void	fork_ps(t_cmd *cmd, char **paths, t_cmdv *cmdv)
{
	char *file;

	if (not_a_path(cmd->argv[0]))
		file = exec_path(paths, cmd->argv[0]);
	else
		file = file_stat(cmd->argv[0]);
	//if file or built-in
	if (file)
	{
		if (cmd->sep == '|' && cmd->sepl != '|')
			pipe_fd_fill(cmd);
		if (cmd->sep == '|' || cmd->sepl == '|')
			pipeline(cmd, file, cmdv);
		else if (cmd->sep == ';' || cmd->sep == 0)
			list(cmd, file, cmdv);
		if (cmd->sep == ';')
			pipe_fd_reset(cmdv->cp);
	}
	else
		error(cmd->argv[0]);
}

void	loop(char **paths)
{
	t_cmd	*cmd;
	t_cmdv	*cmdv;

	while (42)
	{
		ft_putstr_fd("\033[1;31m", 1);
		ft_putstr_fd(">> minishell ", 1);
		ft_putstr_fd("\033[0m", 1);
		if (!(cmd = malloc(sizeof(t_cmd))))
			return ;
		if (!(cmdv = malloc(sizeof(t_cmdv))))
			return ;
		cmdv->cp = cmd;
		if (read_input(cmd, cmdv))
		{
			while (cmd)
			{
				if (!cmd->argv[0] && (cmd->redir == '>' || cmd->redir == '}'))
					create_file(cmd);
				else
					fork_ps(cmd, paths, cmdv);
				cmd = cmd->next;
			}
		}
	}
}

int		main(int argc, char **argv, char **envp)
{
	char *path;
	char **paths;

	(void)argc;
	(void)argv;
	path = get_path(envp);
	paths = split_path(path);
	loop(paths);
	return (0);
}
