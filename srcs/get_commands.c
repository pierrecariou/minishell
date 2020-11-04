/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <pcariou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 09:40:21 by pcariou           #+#    #+#             */
/*   Updated: 2020/11/04 10:43:47 by pcariou          ###   ########.fr       */
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
		cmd = (buf[i]) ? cmd->next : cmd;
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

int		read_input(t_cmd *cmd, t_cmdv *cmdv, char *buf_cp)
{
	//char bufcp[300];

	char *buf;
	int ret;

	//read(0, buf, 300);
	buf = NULL;
	ret = get_next_line(0, &buf);
	//printf("%ld\n", read(0, bufcp, 300));
	//printf("%d\n", ret);
	if (!ret && buf)
	{
		//if (buf_cp && ft_strcmp(buf_cp, buf)) 
		//	cmdv->bufcp = ft_strjoin(buf_cp, buf);
		//else
		cmdv->bufcp = buf;
		//printf("%s", cmdv->bufcp);
		return (0);
	}
	else if  (buf_cp != NULL)
		buf = buf_cp;
//	else if (buf_cp != NULL)
//		buf = ft_strjoin(buf_cp, buf);
	if (!ret && !buf)
	{
		ft_putstr_fd("exit\n", 1);
		exit (0);
	}
	//printf("%d\n", ret);
	//if (ret && buf_cp != NULL)
	//	ft_putstr_fd(buf_cp, 1);
//	printf("%s\n", buf);
	if (!buf[0] || bad_beginning(buf) || bad_ending(buf) ||
			double_sep(buf) || tripledouble_redir(buf) ||
			quotes_not_closed(buf))
		return (0);
	count_envv(buf, cmdv);
	/*
	   int i = 0;
	   while (i < cmdv->nenvv)
	   {
	   printf("TEST ::: %d\n", cmdv->envreplace[i]);
	   i++;
	   }
	 */
	//clean_quotes(buf);
	count_sep(buf, cmdv);
	//printf("%d\n", cmdv->nsep);
	cmd_line(buf, cmd, cmdv);
	free(buf);
	count_redir(cmd);
	get_redirb(cmd);
	get_redir(cmd);
	if (empty_redir(cmd))
		return (0);
	pipe_fd_reset(cmd);
	while (cmd)
	{
		cmd->nforks = 0;
		//better_input(buf);
		cmd->n = count_words(cmd->line, cmdv);
		if (!(cmd->argv = malloc(sizeof(char *) * (cmd->n + 1))))
			return (0);
		malloc_words(cmd->line, cmd->argv, cmd->n, cmdv);
		if (!split_input(cmd->line, cmd->argv, cmd, cmdv))
			return (0);
		cmd->argv[cmd->n] = 0;
		/*
		   int i = -1;
		   while (cmd->argv[++i])
		   printf("word : %s\n", cmd->argv[i]);
		   printf("\n");
		 */
		cmd = cmd->next;
	}
	return (1);
}
