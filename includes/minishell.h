/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <pcariou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 10:54:45 by pcariou           #+#    #+#             */
/*   Updated: 2020/10/12 14:57:49 by pcariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <wait.h>

typedef struct		s_cmd
{
	char			*line;
	char			**argv;
	int				sep;
	int				sepl;
	int				fdout;
	int				fdin;
	int				nforks;
	int				*pid;
	struct	s_cmd	*next;
}					t_cmd;

typedef struct		s_cmdv
{
	struct	s_cmd	*cp;
}					t_cmdv;

void	ft_putstr_fd(char *s, int fd);
int		ft_strcmp(char *s1, char *s2);
int		get_next_line(int fd, char **line);
int		ft_strlen(char *s1);
int		split_input(char *buf, char **words, t_cmd *cmd);
void	malloc_words(char *buf, char **words, int n);
int		count_words(char *buf);
void	better_input(char *buf);
int		read_input(t_cmd *cmd);
int		not_a_path(char *word);
char    *exec_path(char **paths,  char *exec);
char    *file_stat(char *file);
int		ft_isspace(int c);
void	pipe_fd_reset(t_cmd *cmd);
void	pipe_fd_fill(t_cmd *cmd);
char	*get_path(char **envp);
char	**split_path(char *path);
void    pipeline(t_cmd *cmd, char *file, t_cmdv *cmdv);
void	exec_built(char *file, char **argv);

#endif
