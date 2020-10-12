/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <pcariou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 09:40:21 by pcariou           #+#    #+#             */
/*   Updated: 2020/10/12 10:23:03 by pcariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int		find_sep(char c, t_cmd *cmd)
{
	if (c == ';' || c == '|')
	{
		cmd->sep = c;
		return (1);
	}
	return (0);
}

void    split_input(char *buf, char **words)
{
	int i;
	int c;
	int l;

	i = 0;
	c = 0;
	l = 0;
	while (buf[i])
	{
		if (!(ft_isspace(buf[i])))
		{
			while (buf[i] && !(ft_isspace(buf[i])))
			{
				words[c][l] = buf[i];
				i++;
				l++;
			}
			words[c][l] = 0;
			c++;
		}
		else
			i++;
		l = 0;
	}
}

void    malloc_words(char *buf, char **words, int n)
{
	int i;
	int c;
	int l;

	i = -1;
	c = 0;
	l = 0;
	while (++i < n)
	{
		while (buf[c] && ft_isspace(buf[c]))
			c++;
		while (buf[c] && !(ft_isspace(buf[c])))
		{
			c++;
			l++;
		}
		if (!(words[i] = malloc(sizeof(char) * (l + 1))))
			return ;
		l = 0;
	}
}

int             count_words(char *buf)
{
	int i;
	int c;

	i = 0;
	c = 0;
	while (buf[i])
	{
		if (!(ft_isspace(buf[i])))
		{
			c++;
			while (buf[i] && !(ft_isspace(buf[i])))
				i++;
		}
		else
			i++;
	}
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

void	pipe_fd1(t_cmd *cmd)
{
	int fd[2];

	while (cmd->sep == '|' && cmd->next)
	{
		pipe(fd);
		cmd->fdout = fd[1];
		cmd->next->fdin = fd[0];
		cmd = cmd->next;
	}
}

void	pipe_fd(t_cmd *cmd)
{
	//int fd[2];

	while (cmd)
	{
		cmd->fdin = -1;
		cmd->fdout = -1;
		cmd = cmd->next;
	}
	/*
		if (cmd->sep == '|' && cmd->next)
		{
			//printf("%d --- %d\n", fd[0], fd[1]);
			//pipe(fd);	
			//cmd->fdout = fd[1];
			//cmd->next->fdoutp = fd[1];
			//cmd->next->fdin = fd[0];
		}
		cmd = cmd->next;
	}
	*/
}

void	cmd_line(char *buf, t_cmd *cmd)
{
	int i;
	int l;
	int k;

	i = 0;
	k = 0;
	//cmd->next = NULL;
	while (buf[i])
	{
		l = 0;
		k = 0;
		cmd->sep = 0;
		cmd->nforks = 0;
		while (buf[i] && !find_sep(buf[i], cmd))
		{
			l++;
			i++;
		}
		cmd->line = malloc(sizeof(char) * (l + 1));
		i-=l;
		while (buf[i] && !find_sep(buf[i], cmd))
		{
			//printf("%c\n", buf[i]);
			cmd->line[k] = buf[i];
			i++;
			k++;
		}
		cmd->line[k] = 0;
		//cmd->next = 0;
		//printf("%s\n", cmd->line);
		i++;	
		//pipe_fd(cmd);
		if (buf[i])
		{
			//printf("sep : %d\n", sep);
			cmd->next = cmd + sizeof(t_cmd);

			if (!(cmd->next = malloc(sizeof(t_cmd))))
				return ;
			cmd->next->sepl = cmd->sep;
			cmd = cmd->next;
		}
		else
			cmd->next = 0;
	}
}

void	read_input(t_cmd *cmd)
{
	//char buf[300];

	char *buf;
	int n;

	//read(0, buf, 300);
	get_next_line(0, &buf);
	cmd_line(buf, cmd);
	pipe_fd(cmd);
	while (cmd)
	{
		//read(0, buf, 300);
		//better_input(buf);
		n = count_words(cmd->line);
		if (!(cmd->argv = malloc(sizeof(char *) * (n + 2))))
			return ;
		cmd->argv[n] = 0;
		malloc_words(cmd->line, cmd->argv, n);
		split_input(cmd->line, cmd->argv);
		//printf("%s  sep : '%d'\n", cmd->line, cmd->sep);
		cmd = cmd->next;
	}
}
