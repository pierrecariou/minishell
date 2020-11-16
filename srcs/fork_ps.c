/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_ps.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <pcariou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 09:15:02 by pcariou           #+#    #+#             */
/*   Updated: 2020/11/16 10:11:13 by pcariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	error(t_cmd *cmd, t_cmdv *cmdv)
{
	cmdv->error = 1;
	cmdv->error_line = 127;
	if (cmd->redir == '<')
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->redirf, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	else if (cmd->argv[0][0])
	{
		ft_putstr_fd("minishell: command not found: ", 2);
		ft_putstr_fd(cmd->argv[0], 2);
		ft_putstr_fd("\n", 2);
	}
	else
		ft_putstr_fd("minishell: error\n", 2);
	if (cmd->nredir > 1)
		open_files(cmd, cmdv);
	if (cmd->redir && cmd->redir != '<' && cmd->redirf[0])
		create_file(cmd, cmdv);
	if (cmd->redir && cmd->fdredir != -1)
		close(cmd->fdredir);
}

void	exec_built(char *file, char **argv, t_cmd *cmd, t_cmdv *cmdv)
{
	if (cmd->nredir > 1)
		open_files(cmd, cmdv);
	if (cmd->redirl)
	{
		if (!open_file1(cmd))
		{
			error(cmd, cmdv);
			return ;
		}
	}
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
	if (cmd->redirl)
		close(cmd->fdredirl);
	if (cmd->redir)
		close(cmd->fdredir);
	cmdv->error = 0;
}

void	list(t_cmd *cmd, char *file, t_cmdv *cmdv)
{
	int	pid;
	int	status;

	pipe_fd_reset(cmdv->cp);
	status = 0;
	if (!no_fork(cmd->argv))
	{
		if ((pid = fork()) == 0)
		{
			exec_built(file, cmd->argv, cmd, cmdv);
			exit(0);
		}
		waitpid(pid, &status, 0);
	}
	else
		exec_built(file, cmd->argv, cmd, cmdv);
	cmdv->error_line = status;
	cmdv->error = 0;
}

void	fork_ps1(t_cmd *cmd, t_cmdv *cmdv, char *file)
{
	cmdv->error_line = 0;
	if (cmd->sepl == '|' && (cmd->prev->redir || !cmd->prev->active))
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

void	fork_ps(t_cmd *cmd, char **paths, t_cmdv *cmdv, char **envp)
{
	char *file;

	if (not_a_path(cmd->argv[0]))
		file = exec_path(paths, cmd->argv[0]);
	else
		file = file_stat(cmd->argv[0]);
	if ((file || is_built_in(cmd->argv)) &&
			(ft_strcmp(cmd->argv[0], "exit") || cmd->sepl != '|'))
	{
		if (!ft_strcmp(cmd->argv[0], "exit"))
			ft_exit(envp, cmdv, file, paths);
		fork_ps1(cmd, cmdv, file);
	}
	else
		error(cmd, cmdv);
	if (file)
		free(file);
}
