/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <pcariou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 10:54:45 by pcariou           #+#    #+#             */
/*   Updated: 2020/10/28 15:11:35 by pcariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>

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
	int				redir;
	char 			*redirf;
	int				fdredir;
	int				nredir;
	char 			**redirfb;
	struct	s_cmd	*next;
	struct  s_cmd	*prev;
	int				n;
}					t_cmd;

typedef struct		s_cmdv
{
	struct	s_cmd	*cp;
	int				nsep;
	char 			**envp;
	int				error;
	int				error_line;
	int				nenvv;
	int				cenvv;
	int				*envreplace;
	int				inquotess;
	int				inquotesd;
	int				isaquote;
}					t_cmdv;

void	ft_putstr_fd(char *s, int fd);
int		ft_strcmp(char *s1, char *s2);
int		get_next_line(int fd, char **line);
int		ft_strlen(char *s1);
int		split_input(char *buf, char **words, t_cmd *cmd, t_cmdv *cmdv);
void	malloc_words(char *buf, char **words, int n, t_cmdv *cmdv);
int		count_words(char *buf, t_cmdv *cmdv);
void	better_input(char *buf);
int		read_input(t_cmd *cmd, t_cmdv *cmdv);
int		not_a_path(char *word);
char    *exec_path(char **paths,  char *exec);
char    *file_stat(char *file);
int		ft_isspace(int c);
void	pipe_fd_reset(t_cmd *cmd);
void	pipe_fd_fill(t_cmd *cmd);
char	*get_path(char **envp);
char	**split_path(char *path);
void    pipeline(t_cmd *cmd, char *file, t_cmdv *cmdv);
void	exec_built(char *file, char **argv, t_cmd *cmd, t_cmdv *cmdv);
int		double_sep(char *buf);
int 	bad_beginning(char *buf);
int		bad_ending(char *buf);
int		open_file(t_cmd *cmd);
void	open_files(t_cmd *cmd, t_cmdv *cmdv);
int		tripledouble_redir(char *buf);
int		empty_redir(t_cmd *cmd);
void	create_file(t_cmd *cmd, t_cmdv *cmdv);
void	error(t_cmd *cmd, t_cmdv *cmdv);
void	get_redirb(t_cmd *cmd);
void	get_redir(t_cmd *cmd);
void	count_redir(t_cmd *cmd);
char 	*ft_itoa(int nb);
int		ft_cd(t_cmd cmd, t_cmdv *cmdv);
int		cmp_built_in(char **argv, t_cmd *cmd, t_cmdv *cmdv);
int		ft_echo(t_cmd cmd);
int		ft_env(t_cmd cmd, char **envp);
int		ft_pwd(t_cmd cmd);
int		is_built_in(char **argv);
int		ft_export(t_cmd cmd, t_cmdv *cmdv);
size_t	ft_square_strlen(char **str);
char	**ft_square_strjoin(char **tab, char *str);
char	**ft_square_free(char **tab);
char	*ft_strdup(char *s1);
char	*get_envv(char *buf, t_cmdv *cmdv, int i);
void	replace_envv(t_cmd *cmd, t_cmdv *cmdv);
int		is_in_quotes(char *buf, int b, int e);
void	ft_unset(t_cmd cmd, t_cmdv *cmdv);
int		quotes_not_closed(char *buf);
int		is_inquotes(char c, t_cmdv *cmdv);

#endif
