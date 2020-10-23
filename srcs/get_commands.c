/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <pcariou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 09:40:21 by pcariou           #+#    #+#             */
/*   Updated: 2020/10/23 19:18:56 by pcariou          ###   ########.fr       */
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

int		split_input(char *buf, char **words, t_cmd *cmd)
{
	/*
	   while (++i < n)
	   {
	   while (buf[c] && ft_isspace(buf[c]))
	   c++;
	   while (buf[c] && !ft_isspace(buf[c]))
	   {
	   if (buf[c] == '\'' || buf[c] == '\"')
	   {
	   words[i][l] = buf[c];
	   quote = buf[c++];
	   l++;
	   while (buf[c] && buf[c] != quote)
	   {
	   words[i][l] = buf[c];
	   c++;
	   l++;
	   }
	   }
	   words[i][l] = buf[c];
	   c++;
	   l++;
	   }
	   words[i][l] = 0;
	   l = 0;
	   }
	 */
	int i;
	int l;
	int c;
	//char quote;
	int	inquotes;

	//i = -1;
	i = 0;
	c = -1;
	inquotes = 0;
	while (buf[i] && c < cmd->n)
	{
		l = 0;
		if (inquotes == 0 && buf[i] == '~')
			inquotes = 1;
		else if (buf[i] == '~')
			inquotes = 0;
		while (buf[i] && ft_isspace(buf[i]))
			i++;
		if (buf[i] && !ft_isspace(buf[i]) && buf[i] != '~')
		{
			c++;
			while ((buf[i] && !ft_isspace(buf[i]) && inquotes == 0) || 
					(inquotes == 1 && buf[i]))
			{
				if (inquotes == 0 && buf[i] == '~')
					inquotes = 1;
				else if (buf[i] == '~')
					inquotes = 0;
				else
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

void    malloc_words(char *buf, char **words, int n)
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
	while (buf[i] && k < n)
	{
		l = 0;
		if (inquotes == 0 && buf[i] == '~')
			inquotes = 1;
		else if (buf[i] == '~')
			inquotes = 0;
		while (buf[i] && ft_isspace(buf[i]))
			i++;
		if (buf[i] && !ft_isspace(buf[i]) && buf[i] != '~')
		{
			while ((buf[i] && !ft_isspace(buf[i]) && inquotes == 0) || 
					(inquotes == 1 && buf[i]))
			{
				if (inquotes == 0 && buf[i] == '~')
					inquotes = 1;
				else if (buf[i] == '~')
					inquotes = 0;
				else
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

int             count_words(char *buf)
{
	int c;
	int i;
	int inquotes;

	c = 0;
	i = 0;
	inquotes = 0;
	while (buf[i])
	{
		if (inquotes == 0 && buf[i] == '~')
			inquotes = 1;
		else if (buf[i] == '~')
			inquotes = 0;
		while (buf[i] && ft_isspace(buf[i]))
			i++;
		if (buf[i] && !ft_isspace(buf[i]) && buf[i] != '~')
		{
			c++;
			while ((buf[i] && !ft_isspace(buf[i]) && inquotes == 0) || 
					(inquotes == 1 && buf[i]))
			{
				if (inquotes == 0 && buf[i] == '~')
					inquotes = 1;
				else if (buf[i] == '~')
					inquotes = 0;
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
		l = 0;
		k = 0;
		cmd->sep = 0;
		while (buf[i] && !find_sep(buf, cmd, i, inquotes))
		{
			if (inquotes == 0 && buf[i] == '~')
				inquotes = 1;
			else if (buf[i] == '~')
				inquotes = 0;
			l++;
			i++;
		}
		cmd->line = malloc(sizeof(char) * (l + 1));
		i-=l;
		while (buf[i] && !find_sep(buf, cmd, i, inquotes))
		{
			if (inquotes == 0 && buf[i] == '~')
				inquotes = 1;
			else if (buf[i] == '~')
				inquotes = 0;
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

/*
int		is_in_quotes(char *buf, int b, int e)
{
	while (b >= 0 && ft_isspace(buf[b]))
		b--;
	if (b >= 0 && (buf[b] == '\'' || buf[b] == '\"'))
		return (1);
	while  (buf[e] && ft_isspace(buf[e]))
		e++;
	if (buf[e] && (buf[e] == '\'' || buf[e] == '\"'))
		return (1);
	return (0);	
}
*/

void	count_sep(char *buf, t_cmdv *cmdv)
{
	int i;
	int inquotes;

	i = -1;
	cmdv->nsep = 0;
	inquotes = 0;
	while (buf[++i])
	{
		if (inquotes == 0 && buf[i] == '~')
			inquotes = 1;
		else if (buf[i] == '~')
			inquotes = 0;
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

int		read_input(t_cmd *cmd, t_cmdv *cmdv)
{
	//char buf[300];

	char *buf;

	//read(0, buf, 300);
	get_next_line(0, &buf);
	if (!buf[0] || bad_beginning(buf) || bad_ending(buf) ||
			double_sep(buf) || tripledouble_redir(buf) ||
			quotes_not_closed(buf))
		return (0);
	clean_quotes(buf);
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
		cmd->n = count_words(cmd->line);
		if (!(cmd->argv = malloc(sizeof(char *) * (cmd->n + 1))))
			return (0);
		malloc_words(cmd->line, cmd->argv, cmd->n);
		if (!split_input(cmd->line, cmd->argv, cmd))
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
