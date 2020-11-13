/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <pcariou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 10:53:46 by pcariou           #+#    #+#             */
/*   Updated: 2020/11/13 11:47:23 by pcariou          ###   ########.fr       */
/*                                                                            */
/* **************************************************************************/

#include "includes/minishell.h"

int		g_handler;

void	inthandler(int num) 
{
	(void)num;

	ft_putstr_fd("\n", 0);
	ft_putstr_fd("\033[1;31m", 0);
	ft_putstr_fd("The-Minishell-Project", 0);
	ft_putstr_fd("\033[0m", 0);
	ft_putstr_fd("$ ", 0);
	g_handler = 1;
	return ;
}

void	quithandler(int num) 
{

	(void)num;
	
	ft_putstr_fd("\33[2D", 0);
	ft_putstr_fd("  ", 0);
	ft_putstr_fd("\33[2D", 0);
	return ;
}

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

void		exec_built(char *file, char **argv, t_cmd *cmd, t_cmdv *cmdv)
{
	//if (strcmp(argv[0], "echo") || ...)
	// built_in();
	//else
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
	int pid;
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

void	fork_ps(t_cmd *cmd, char **paths, t_cmdv *cmdv, char **envp)
{
	char *file;

	if (not_a_path(cmd->argv[0]))
		file = exec_path(paths, cmd->argv[0]);
	else
		file = file_stat(cmd->argv[0]);
	//if file or built-in
	if ((file || is_built_in(cmd->argv)) && (ft_strcmp(cmd->argv[0], "exit") || cmd->sepl != '|'))
	{
		if (!ft_strcmp(cmd->argv[0], "exit"))
			ft_exit(envp, cmdv, file, paths);
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
	else
		error(cmd, cmdv);
	if (file)
		free(file);
}


void	free_structs(t_cmdv *cmdv)
{
	int i;
	t_cmd *cp;


	while (cmdv->cp)	
	{
		i = -1;
		if (cmdv->cp->line)
			free(cmdv->cp->line);
		while (cmdv->cp->argv && cmdv->cp->argv[++i])
			free(cmdv->cp->argv[i]);
		if (cmdv->cp->argv)
			free(cmdv->cp->argv);
		if (cmdv->cp->pid)
			free(cmdv->cp->pid);
		if (cmdv->cp->redirf)	
			free(cmdv->cp->redirf);
		if (cmdv->cp->redirfl)	
			free(cmdv->cp->redirfl);
		i = -1;
		while (cmdv->cp->redirfb && cmdv->cp->redirfb[++i])
				free(cmdv->cp->redirfb[i]);
		if (cmdv->cp->redirfb)
			free(cmdv->cp->redirfb);
		cp = cmdv->cp;
		cmdv->cp = cmdv->cp->next;
		free(cp);
	}
	if (cmdv->envreplace)
		free(cmdv->envreplace);
	free(cmdv);
}

void	loop(char **envp)
{
	t_cmd	*cmd;
	t_cmdv	*cmdv;
	int 	error_line;
	int		parse;
	char	**paths;
	char	*path;

	error_line = 0;	
	while (42)
	{
		if (g_handler)
			ft_putstr_fd("\33[2K\r", 0);
		g_handler = 0;
		ft_putstr_fd("\033[1;31m", 0);
		ft_putstr_fd("The-Minishell-Project", 0);
		ft_putstr_fd("\033[0m", 0);
		ft_putstr_fd("$ ", 0);
		if (!(cmd = malloc(sizeof(t_cmd))))
			return ;
		if (!(cmdv = malloc(sizeof(t_cmdv))))
			return ;
		cmd->next = 0;
		cmd->line = NULL;
		cmd->argv = NULL;
		cmd->pid = NULL;
		cmd->redirf = NULL;
		cmd->redirfb = NULL;
		cmdv->envreplace = NULL;
		cmdv->envp = envp;
		cmdv->cp = cmd;
		cmdv->error = 0;
		cmdv->cenvv = 0;
		cmdv->error_line = error_line;
		if ((parse = read_input(cmd, cmdv, paths, envp)))
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
				path = get_path(cmdv->envp);
				if (path == NULL)
					paths = NULL;
				else
				{
					path = ft_strdup(path);
					paths = split_path(path);
					free(path);
				}
				if (cmdv->error_line && cmdv->error_line != 127)
					cmdv->error_line = 2;
				if (cmd->active)
				{
				replace_envv(cmd, cmdv);
				if (!cmd->argv[0] && (cmd->redir == '>' || cmd->redir == '}'))
					create_file(cmd, cmdv);
				if (!cmd->argv[0])
						cmdv->error = 1;
				else
					fork_ps(cmd, paths, cmdv, envp);
				}
				cmd = cmd->next;
				free_paths(paths, envp, 1);
			}
		}
		else if (!cmdv->empty)
			ft_putstr_fd("minishell: syntax error\n", 2);
		if (!parse || (cmdv->error_line != 0 && cmdv->error_line != 127))
			error_line = 2;
		else if (parse)
			error_line = cmdv->error_line;
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
	signal(SIGINT, inthandler);
	//signal(SIGHUP, huphandler);
	signal(SIGQUIT, quithandler);
	tmp_env = ft_square_strjoin(envp, NULL);
	loop(tmp_env);
	return (0);
}
