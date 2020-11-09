/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <pcariou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 09:40:21 by pcariou           #+#    #+#             */
/*   Updated: 2020/11/09 11:57:22 by pcariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int		find_sep(char *buf, t_cmd *cmd, int i, int inquotes)
{
	if (buf[i] == ';' || buf[i] == '|')
	{
		if (inquotes == 1)
			return (0);
		cmd->sep = buf[i];
		return (1);
	}
	return (0);
}

int		split_input(char *buf, char **words, t_cmd *cmd, t_cmdv *cmdv)
{
	int i;
	int l;
	int c;
	int	inquotes;

	i = 0;
	c = -1;
	inquotes = 0;
	cmdv->inquotess = 0;
	cmdv->inquotesd = 0;
	while (buf[i] && c < cmd->n)
	{
		l = 0;
		inquotes = is_inquotes(buf[i], cmdv);
		while (buf[i] && ft_isspace(buf[i]))
			i++;
		if (buf[i] && !ft_isspace(buf[i]) && !cmdv->isaquote)
		{
			c++;
			while ((buf[i] && !ft_isspace(buf[i]) && inquotes == 0) || 
					(inquotes == 1 && buf[i]))
			{
				inquotes = is_inquotes(buf[i], cmdv);
				if (!cmdv->isaquote)
					words[c][l++] = buf[i];
				i++;
			}
			if (l > 0)
				words[c][l] = 0;
		}
		if (buf[i])
			i++;
	}
	if (!cmd->next && cmd->sep == '|')
		return (0);
	return (1);
}

void    malloc_words(char *buf, char **words, int n, t_cmdv *cmdv)
{
	int i;
	int l;
	int k;
	//char quote;
	int	inquotes;

	//i = -1;
	i = 0;
	k = 0;
	inquotes = 0;
	cmdv->inquotess = 0;
	cmdv->inquotesd = 0;
	while (buf[i] && k < n)
	{
		l = 0;
		inquotes = is_inquotes(buf[i], cmdv);
		while (buf[i] && ft_isspace(buf[i]))
			i++;
		if (buf[i] && !ft_isspace(buf[i]) && !cmdv->isaquote)
		{
			while ((buf[i] && !ft_isspace(buf[i]) && inquotes == 0) || 
					(inquotes == 1 && buf[i]))
			{
				inquotes = is_inquotes(buf[i], cmdv);
				if (!cmdv->isaquote)
					l++;
				i++;
			}
			if (l > 0)
			{
				//printf("testlength : %d\n", l);
				if (!(words[k++] = malloc(sizeof(char) * (l + 1))))
					return ;
			}
		}
		if (buf[i])
			i++;
	}
	//printf("FINISH\n");
}

int             count_words(char *buf, t_cmdv *cmdv)
{
	int c;
	int i;
	int inquotes;

	c = 0;
	i = 0;
	inquotes = 0;
	cmdv->inquotess = 0;
	cmdv->inquotesd = 0;
	while (buf[i])
	{
		inquotes = is_inquotes(buf[i], cmdv);
		while (buf[i] && ft_isspace(buf[i]))
			i++;
		if (buf[i] && !ft_isspace(buf[i]) && !cmdv->isaquote)
		{
			c++;
			while ((buf[i] && !ft_isspace(buf[i]) && inquotes == 0) || 
					(inquotes == 1 && buf[i]))
			{
				inquotes = is_inquotes(buf[i], cmdv);
				i++;
			}
		}
		if (buf[i])
			i++;
	}
	//printf("nwords : %d\n", c);
	return (c);
}

/*
   void    better_input(char *buf)
   {
   int i;

   i = 0;
   while (buf[i] >= 31 && buf[i] < 127)
   i++;
   buf[i] = 0;
   }
 */

void	add_next(int m, t_cmd *cmd, t_cmdv *cmdv)
{
	t_cmd *next;

	if (m == 0)
		cmd->sepl = 0;
	if (m + 1 < cmdv->nsep + 1)
	{
		if (!(next = malloc(sizeof(t_cmd))))
			return ;	
		next->sepl = cmd->sep;
		cmd->next = next;
		cmd->next->prev = cmd;
	}
	else
		cmd->next = 0;	
}

void	cmd_line(char *buf, t_cmd *cmd, t_cmdv *cmdv)
{
	int i;
	int l;
	int k;
	int m;
	int inquotes;

	i = 0;
	m = -1;
	while (++m < cmdv->nsep + 1)
	{
		inquotes = 0;
		cmdv->inquotess = 0;
		cmdv->inquotesd = 0;
		l = 0;
		k = 0;
		cmd->sep = 0;
		while (buf[i] && !find_sep(buf, cmd, i, inquotes))
		{
			inquotes = is_inquotes(buf[i], cmdv);
			l++;
			i++;
		}
		cmd->line = malloc(sizeof(char) * (l + 1));
		i-=l;
		while (buf[i] && !find_sep(buf, cmd, i, inquotes))
		{
			inquotes = is_inquotes(buf[i], cmdv);
			cmd->line[k] = buf[i];
			i++;
			k++;
		}
		cmd->line[k] = 0;
		i++;	
		add_next(m, cmd, cmdv);
		cmd = cmd->next;
	}
}

void	count_sep(char *buf, t_cmdv *cmdv)
{
	int i;
	int inquotes;

	i = -1;
	cmdv->nsep = 0;
	inquotes = 0;
	cmdv->inquotess = 0;
	cmdv->inquotesd = 0;
	while (buf[++i])
	{
		inquotes = is_inquotes(buf[i], cmdv);
		if ((buf[i] == '|' || buf[i] == ';')
				&& inquotes == 0)
			cmdv->nsep++;
	}
}

void	clean_quotes(char *buf)
{
	int i;
	char c;

	c = 0;
	i = 0;
	while (buf[i])
	{
		while (buf[i] && c == 0)
		{
			if ((buf[i] == '\"' || buf[i] == '\''))
			{
				c = buf[i];
				buf[i] = 126;
			}
			i++;
		}
		while (buf[i] && c != 0)
		{
			if (buf[i] == c)
			{
				c = 0;
				buf[i] = 126;
			}
			i++;
		}
	}
	//printf("%s\n", cmd->line);
}

int		is_inquotes(char c, t_cmdv *cmdv)
{
	cmdv->isaquote = 0;
	if (cmdv->inquotesd == 0 && c == '\"' && cmdv->inquotess == 0)
		cmdv->inquotesd = 1;
	else if (cmdv->inquotess == 0 && c == '\'' && cmdv->inquotesd == 0)
		cmdv->inquotess = 1;
	else if (c == '\"' && cmdv->inquotess == 0)
		cmdv->inquotesd = 0;
	else if (c == '\'' && cmdv->inquotesd == 0)
		cmdv->inquotess = 0;
	else
		return (cmdv->inquotess + cmdv->inquotesd);
	cmdv->isaquote = 1;
	return (cmdv->inquotess + cmdv->inquotesd);
}

void	count_envv(char *buf, t_cmdv *cmdv)
{
	int i;
	int m;

	i = -1;
	m = -1;
	cmdv->nenvv = 0;;
	cmdv->inquotesd = 0;
	cmdv->inquotess = 0;
	while (buf[++i])
	{
		if (buf[i] == '$')
			cmdv->nenvv++;
	}
	if (!cmdv->nenvv)
		return ;
	//	printf("CENVV ::: %d\n", cmdv->nenvv);
	if (!(cmdv->envreplace = malloc(sizeof(int) * cmdv->nenvv)))
		return ;
	i = -1;
	while (buf[++i])
	{
		is_inquotes(buf[i], cmdv);
		if (buf[i] == '$' && cmdv->inquotess)
			cmdv->envreplace[++m] = 0;
		else if (buf[i] == '$')
			cmdv->envreplace[++m] = 1;
	}
}

void	init(t_cmd *cmd)
{
	t_cmd *cp;

	cp = cmd;
	while (cp)
	{
		cp->argv = NULL;
		cp->pid = NULL;
		cp->redirf = NULL;
		cp->redirfb = NULL;
		cp = cp->next;
	}
}

void	free_paths(char **paths, char **envp)
{
	int i;

	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	i = -1;
	while (envp[++i])
		free(envp[i]);
	free(envp);
}

int		read_input(t_cmd *cmd, t_cmdv *cmdv, char **paths, char **envp)
{
	//char bufcp[300];

	char *buf;
	int ret;
	char *buf_cp;

	//read(0, buf, 300);
	buf = NULL;
	buf_cp = NULL;
	while ((ret = get_next_line(0, &buf)) == 0 && buf)
	{		
			buf_cp = buf;
			free(buf);
			buf = NULL;
			
	}
	if (ret == 1 && !buf[0] && buf_cp != NULL)
		buf = buf_cp;
	if (!ret && !buf)
	{
		free(cmd);
		free(cmdv);
		free_paths(paths, envp);
		ft_putstr_fd("exit\n", 1);
		exit (0);
	}
	cmdv->empty = (buf[0]) ? 0 : 1;
	if (!buf[0] || bad_beginning(buf) || bad_ending(buf) ||
			double_sep(buf) || tripledouble_redir(buf) ||
			quotes_not_closed(buf))
	{
		free(buf);
		return (0);
	}
	count_envv(buf, cmdv);
	//clean_quotes(buf);
	count_sep(buf, cmdv);
	//printf("%d\n", cmdv->nsep);
	//cmd->line = NULL;
	cmd_line(buf, cmd, cmdv);
	free(buf);
	init(cmd);
	count_redir(cmd);
	get_redirb(cmd);
	get_redir(cmd);
	if (empty_redir(cmd))
		return (0);
	pipe_fd_reset(cmd);
	while (cmd)
	{
		cmd->active = 1;
		cmd->nforks = 0;
		//better_input(buf);
		cmd->n = count_words(cmd->line, cmdv);
		if (!(cmd->argv = malloc(sizeof(char *) * (cmd->n + 1))))
			return (0);
		malloc_words(cmd->line, cmd->argv, cmd->n, cmdv);
		if (!split_input(cmd->line, cmd->argv, cmd, cmdv))
			return (0);
		cmd->argv[cmd->n] = 0;
		cmd = cmd->next;
	}
	fork_error(cmdv);
	return (1);
}
