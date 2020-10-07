/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <pcariou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 10:53:46 by pcariou           #+#    #+#             */
/*   Updated: 2020/10/07 07:56:05 by pcariou          ###   ########.fr       */
/*                                                                            */
/* **************************************************************************/

#include "minishell.h"

/*
void	handler(int num) 
{
	(void)num;
	write(1, "handling!\n", 10);
}
*/
/*

void	check_echo(char *buf)
{
	ft_putstr_fd(buf, 1);	
}

void	check_input(char *buf)
{
	if (ft_strcmp(buf, "echo") == 0)
		check_echo(buf);
	else
	{
		ft_putstr_fd("command not found: ", 1);
		ft_putstr_fd(buf, 1);
	}
	ft_putstr_fd("\n", 1);
}
*/

void	split_input(char *buf, char **words)
{
	int i;
	int c;
	int l;

	i = 0;
	c = 0;
	l = 0;
	while (buf[i])
	{
		if (buf[i] != ' ')
		{
		while (buf[i] && buf[i] != ' ')
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

void	malloc_words(char *buf, char **words, int n)
{
	int i;
	int c;
	int l;

	i = -1;
	c = 0;
	l = 0;
	while (++i < n)
	{
		while (buf[c] && buf[c] == ' ')
			c++;
		while (buf[c] && buf[c] != ' ')
		{
			c++;
			l++;
		}
		words[i] = malloc(sizeof(char) * (l + 1));
		l = 0;
	}
}

int		count_words(char *buf)
{
	int i;
	int c;

	i = 0;
	c = 0;
	while (buf[i])
	{
		if (buf[i] != ' ')
		{
			c++;
		while (buf[i] && buf[i] != ' ')
			i++;
		}
		else
			i++;
	}
	return (c);
}

void	better_input(char *buf)
{
	int i;

	i = 0;
	while (buf[i] > 31 && buf[i] < 127)
		i++;
	buf[i] = 0;
}

void	read_input(void)
{
	//char buf[300];
	int n;
	char *buf;
	char **words;

	//read(0, buf, 300);
	(void)n;
	get_next_line(0, &buf);
	better_input(buf);
	n = count_words(buf);
	words = malloc(sizeof(char *) * (n + 1));
	words[n] = 0;
	malloc_words(buf, words, n);
	split_input(buf, words);
	/*
	int i = -1;
	while (words[++i])
		printf("%s\n", words[i]);
	*/
	//check_input(buf);
}

void	loop(void)
{
	while (42)
	{
		ft_putstr_fd("\033[1;31m", 1);
		ft_putstr_fd(">> minishell ", 1);
		ft_putstr_fd("\033[0m", 1);
		read_input();
		/*
		if (fork() == 0)
			execve("/bin.sh", "ls", "-lp", NULL);
		else
			wait(NULL);
			*/
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
	paths = malloc(sizeof(char *) * (k + 2));
	paths[k + 2] = 0;
	//printf("%d\n", k + 2);
	m = -1;
	i = -1;
	while (++m < k + 1)
	{
		while (path[++c] && path[c] != ':')
			c = c;
		//printf("%d\n", c - i);
		paths[m] = malloc(sizeof(char) * (c - i));
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
	loop();
	return (0);
}
