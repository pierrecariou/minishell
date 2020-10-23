/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <pcariou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 10:53:46 by pcariou           #+#    #+#             */
/*   Updated: 2020/10/23 18:54:24 by pcariou          ###   ########.fr       */
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
void	error(t_cmd *cmd, t_cmdv *cmdv)
{
	cmdv->error = 1;
	cmdv->error_line = 127;
	if (cmd->redir == '<')
	{
		ft_putstr_fd(cmd->redirf, 1);
		ft_putstr_fd(": No such file or directory\n", 1);
	}
	else if (cmd->argv[0][0])
	{
		ft_putstr_fd("command not found: ", 1);
		ft_putstr_fd(cmd->argv[0], 1);
		ft_putstr_fd("\n", 1);
	}
	else
		ft_putstr_fd("error\n", 2);
	if (cmd->nredir > 1)
		open_files(cmd, cmdv);
	if (cmd->redir && cmd->redir != '<' && cmd->redirf[0])
		create_file(cmd, cmdv);
	if (cmd->redir)
		close(cmd->fdredir);
}

void		exec_built(char *file, char **argv, t_cmd *cmd, t_cmdv *cmdv)
{
	//if (strcmp(argv[0], "echo") || ...)
	// built_in();
	//else
	if (cmd->nredir > 1)
		open_files(cmd, cmdv);
	if (cmd->redir)
	{
		if (!open_file(cmd))
		{
			error(cmd, cmdv);
			return ;
		}
	}
	if (!cmp_built_in(argv, cmd, cmdv))
		execve(file, argv, NULL);
	if (cmd->redir)
		close(cmd->fdredir);
	cmdv->error = 0;
}

void	list(t_cmd *cmd, char *file, t_cmdv *cmdv)
{
	int pid;
	int	status;

	pipe_fd_reset(cmdv->cp);
	if ((pid = fork()) == 0)
	{
		exec_built(file, cmd->argv, cmd, cmdv);
		if (is_built_in(cmd->argv) && cmd->redir)
			exit(0);
	}
	waitpid(pid, &status, 0);
	cmdv->error_line = status;
	cmdv->error = 0;
}

/*
int		valid_cmd(t_cmd *cmd, char **paths)
{
	char *file;

	if (!cmd->argv[0])
		return (1);
	if (not_a_path(cmd->argv[0]))
		file = exec_path(paths, cmd->argv[0]);
	else
		file = file_stat(cmd->argv[0]);
	if (file)
		return (0);
	return (1);
}
*/

void	fork_ps(t_cmd *cmd, char **paths, t_cmdv *cmdv)
{
	char *file;

	if (not_a_path(cmd->argv[0]))
		file = exec_path(paths, cmd->argv[0]);
	else
		file = file_stat(cmd->argv[0]);
	//if file or built-in
	if (file || is_built_in(cmd->argv))
	{	
		cmdv->error_line = 0;
		if (cmd->sepl == '|' && cmd->prev->redir)
		{
			cmd->sepl = ' ';
			pipe_fd_reset(cmdv->cp);
		}
		if ((cmd->sep == '|' && cmd->sepl != '|')
			&& cmdv->error == 0)
			pipe_fd_fill(cmd);
		if ((cmd->sep == '|' || cmd->sepl == '|')
			&& cmdv->error == 0)
			pipeline(cmd, file, cmdv);
		else if ((cmd->sep == ';' || cmd->sep == 0)
			&& !(cmd->sepl == '|' && cmdv->error == 1))
			list(cmd, file, cmdv);
		if (cmd->sep == ';')
			pipe_fd_reset(cmdv->cp);
	}
	else
		error(cmd, cmdv);
}

void	loop(char **paths, char **envp)
{
	t_cmd	*cmd;
	t_cmdv	*cmdv;
	int 	error_line;
	int		parse;
	
	error_line = 0;
	while (42)
	{
		ft_putstr_fd("\033[1;31m", 1);
		ft_putstr_fd(">> minishell ", 1);
		ft_putstr_fd("\033[0m", 1);
		if (!(cmd = malloc(sizeof(t_cmd))))
			return ;
		if (!(cmdv = malloc(sizeof(t_cmdv))))
			return ;
		cmdv->envp = envp;
		cmdv->cp = cmd;
		cmdv->error = 0;
		cmdv->error_line = error_line;
		if ((parse = read_input(cmd, cmdv)))
		{
			while (cmd)
			{
				/*
				int i = -1;
				while (cmd->argv[++i])
					printf("word : %s\n", cmd->argv[i]);
				printf("n : %d\n", cmd->n);
				printf("\n");
				*/
				replace_envv(cmd, cmdv);
				if (!cmd->argv[0] && (cmd->redir == '>' || cmd->redir == '}'))
					create_file(cmd, cmdv);
				if (!cmd->argv[0])
					cmdv->error = 1;
				else
					fork_ps(cmd, paths, cmdv);
				cmd = cmd->next;
			}
		}
		if (!parse || (cmdv->error_line != 0 && cmdv->error_line != 127))
			error_line = 2;
		else if (parse)
			error_line = cmdv->error_line;
		envp = cmdv->envp;
		free(cmd);
		free(cmdv);
	}
}

int		main(int argc, char **argv, char **envp)
{
	char *path;
	char **paths;
	char **tmp_env;

	(void)argc;
	(void)argv;
	tmp_env = ft_square_strjoin(envp, NULL);
	path = get_path(envp);
	paths = split_path(path);
	loop(paths, tmp_env);
	return (0);
}
