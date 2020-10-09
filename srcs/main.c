/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <pcariou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 10:53:46 by pcariou           #+#    #+#             */
/*   Updated: 2020/10/09 18:56:53 by pcariou          ###   ########.fr       */
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


void	pipeline(t_cmd *cmd, char *file)
{
	(void)cmd;
	(void)file;
	int pid;
	int i;
// faire les pipe avec un tableau en ayant tout compte au prealable

	i = 0;
	pid = fork();
	if (pid == 0)
	{
	if (cmd->sepl == '|')
	{
		dup2(cmd->fdin, 0);
		close(cmd->fdoutp);
		close(cmd->fdin);
		execve(file, cmd->argv, NULL);		
	}
	if (cmd->sep == '|')
	{
		dup2(cmd->fdout, 1);
		close(cmd->next->fdin);
		close(cmd->fdout);
		execve(file, cmd->argv, NULL);
		cmd->next->nforks = cmd->nforks + 1;
		cmd->next->pid = malloc(sizeof(int) * cmd->next->nforks);
		while (i < cmd->nforks)
		{
			cmd->next->pid[i] = cmd->pid[i];
			i++;
		}
		cmd->next->pid[i] = pid;
	}
	}
	else if (cmd->sep != '|')
	{
		i = 0;
		while (i < cmd->nforks)
		{
			waitpid(cmd->pid[i], NULL, 0);
			i++;			
		}
		waitpid(pid, NULL, 0);	
		close(3);
		close(4);
	}
}

/*
void	pipeline(t_cmd *cmd, char *file)
{
	(void)cmd;
	(void)file;

}
*/

void	list(t_cmd *cmd, char *file)
{
	if (fork() == 0)
		{
			//printf("%s  %s\n", path, words[0]);
			execve(file, cmd->argv, NULL);
		}
		else
			wait(NULL);
}

void	fork_ps(t_cmd *cmd, char **paths)
{
	char *file;
	
	if (not_a_path(cmd->argv[0]))
		file = exec_path(paths, cmd->argv[0]);
	else
		file = file_stat(cmd->argv[0]);
	//printf("%s\n", path);
	if (file)
	{
	if (cmd->sep == '|' || cmd->sepl == '|')
		pipeline(cmd, file);
	else if (cmd->sep == ';' || cmd->sep == 0)
		list(cmd, file);
	}
	else
		error(cmd->argv[0]);
	//printf("TEST sepl: %d\n", cmd->sepl);
	//printf("TEST sep: %d\n", cmd->sep);
}

void	loop(char **paths)
{
	t_cmd	*cmd;
	//char **words;
	//char *file;

	//(void)words;
	(void)paths;
	//cmd = NULL;
	while (42)
	{
		ft_putstr_fd("\033[1;31m", 1);
		ft_putstr_fd(">> minishell ", 1);
		ft_putstr_fd("\033[0m", 1);
		if (!(cmd = malloc(sizeof(t_cmd))))
			return ;
		read_input(cmd);
		while (cmd)
		{
			fork_ps(cmd, paths);
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
	//printf("%d\n", k + 2);
	m = -1;
	i = -1;
	while (++m < k + 1)
	{
		while (path[++c] && path[c] != ':')
			c = c;
		//printf("%d\n", c - i);
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
	//path[ft_strlen(path) + 1] = 0;
	//printf("T>EST --- %s\n", path);
	//printf("%d\n", ft_strlen(path));
	paths = split_path(path);
	/*
	   int i = -1;
	   while (paths[++i])
	   printf("%s\n", paths[i]);
	 */
	loop(paths);
	return (0);
}
