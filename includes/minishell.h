/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <pcariou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 10:54:45 by pcariou           #+#    #+#             */
/*   Updated: 2020/10/07 11:11:27 by pcariou          ###   ########.fr       */
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

void	ft_putstr_fd(char *s, int fd);
int		ft_strcmp(char *s1, char *s2);
int		get_next_line(int fd, char **line);
int		ft_strlen(char *s1);
void	split_input(char *buf, char **words);
void	malloc_words(char *buf, char **words, int n);
int		count_words(char *buf);
void	better_input(char *buf);
char	**read_input(void);

#endif
