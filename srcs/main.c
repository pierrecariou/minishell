/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <pcariou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 10:53:46 by pcariou           #+#    #+#             */
/*   Updated: 2020/10/12 11:07:29 by pcariou          ###   ########.fr       */
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
	ft_putstr_fd("command not found: ", 1);
	ft_putstr_fd(buf, 1);
	ft_putstr_fd("\n", 1);
}

void		store_pid(t_cmd *cmd, int pid)
{
	int i;

	i = -1;
	cmd->next->nforks = cmd->nforks + 1;
	if (!(cmd->next->pid = malloc(sizeof(int) * cmd->next->nforks)))
		return ;
	while (++i < cmd->nforks)
		cmd->next->pid[i] = cmd->pid[i];
	i++;
	cmd->next->pid[i] = pid;
}

void		close_fd(t_cmdv *cmdv)
{
	t_cmd *cp;

	cp = cmdv->cp;
	while (cp->next)
	{
		if (cp->fdout != -1)
			close(cp->fdout);
		if (cp->next->fdin != -1)
			close(cp->next->fdin);
		cp = cp->next;
	}
}

void	pipeline(t_cmd *cmd, char *file, t_cmdv *cmdv)
{
	int pid;
	int i;

	i = -1;
	pid = fork();
	if (pid == 0)
	{
		if (cmd->sepl == '|')
			dup2(cmd->fdin, 0);
		if (cmd->sep == '|')
			dup2(cmd->fdout, 1);
		close_fd(cmdv);
		execve(file, cmd->argv, NULL);
	}
	if (cmd->sep == '|')
		store_pid(cmd, pid);
	else
	{
		close_fd(cmdv);
		while (++i < cmd->nforks)
			waitpid(cmd->pid[i], NULL, 0);
		waitpid(pid, NULL, 0);
	}
}

void	list(t_cmd *cmd, char *file, t_cmdv *cmdv)
{
	int pid;

	pipe_fd_reset(cmdv->cp);
	if ((pid = fork()) == 0)
		execve(file, cmd->argv, NULL);
	waitpid(pid, NULL, 0);
}

void	fork_ps(t_cmd *cmd, char **paths, t_cmdv *cmdv)
{
	char *file;

	if (not_a_path(cmd->argv[0]))
		file = exec_path(paths, cmd->argv[0]);
	else
		file = file_stat(cmd->argv[0]);
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
	//t_cmd 	*cp;

	(void)paths;
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
		read_input(cmd);
		while (cmd)
		{
			fork_ps(cmd, paths, cmdv);
			cmd = cmd->next;
		}
	}
}

char **split_path(char *path)
{
	char **paths;
	int i;
	int c;
	int k;
	int l;
	int m;

	i = -1;
	c = -1;
	k = 0;
	l = 0;
	m = 0;
	while (path[++i])
		k = (path[i] == ':') ? k + 1 : k;
	if (!(paths = malloc(sizeof(char *) * (k + 2))))
		return (0);
	paths[k + 2] = 0;
	m = -1;
	i = -1;
	while (++m < k + 1)
	{
		while (path[++c] && path[c] != ':')
			c = c;
		if (!(paths[m] = malloc(sizeof(char) * (c - i))))
			return (0);
		while (path[++i] && path[i] != ':')
			paths[m][l++] = path[i];
		paths[m][l] = 0;
		l = 0;
	}
	return (paths);
}

char	*get_path(char **envp)
{
	int i;

	i = -1;
	while (envp[++i])
	{
		if (envp[i][0] == 'P' && envp[i][1] == 'A'
				&& envp[i][2] == 'T' && envp[i][3] == 'H'
				&& envp[i][4] == '=')
			return (&envp[i][5]);
	}
	return (0);
}

int		main(int argc, char **argv, char **envp)
{
	char *path;
	char **paths;

	(void)argc;
	(void)argv;
	(void)paths;
	path = get_path(envp);
	paths = split_path(path);
	loop(paths);
	return (0);
}
