/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 14:11:21 by pcariou           #+#    #+#             */
/*   Updated: 2020/01/21 11:54:29 by pcariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifdef BUFFER_SIZE
#  if BUFFER_SIZE < 0
#   undef BUFFER_SIZE
#   define BUFFER_SIZE 0
#  endif
# endif

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 300
# endif

int		get_next_line(int fd, char **line);
int		count_lines(char *buf);
char	*create_line(char *buf, int b, int e, char *line_cut);
char	*ft_strjoin(char *s1, char *s2);

#endif
