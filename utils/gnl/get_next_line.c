/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 19:50:06 by pcariou           #+#    #+#             */
/*   Updated: 2020/11/09 11:15:40 by pcariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	**end_of_line(char *buf, char **lines, const char *line_cut, int *i)
{
	if (i[2] == 0)
	{
		if (!(lines = malloc(sizeof(char *) * count_lines(buf))))
			return (0);
	}
	lines[i[2]] = create_line(buf, i[0], i[1] - 1, (char *)line_cut);
	i[2]++;
	i[0] = i[1] + 1;
	return (lines);
}

/*
** i[0] = b;
** i[1] = e;
** i[2] = l;
*/

char	**create_lines(char *buf, int alt)
{
	int			i[3];
	static int	cp;
	char		**lines;
	static char *line_cut;

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	lines = NULL;
	line_cut = (cp == 1 && alt == 0) ? NULL : line_cut;
	cp = (cp == 1 && alt == 0) ? 0 : cp;
	cp = alt;
	if (alt == 1)
		return (line_cut) ? &line_cut : NULL;
	line_cut = (line_cut) ? line_cut : NULL;
	while (buf[i[1]])
	{
		if (buf[i[1]] == '\n' && (lines = end_of_line(buf, lines, line_cut, i)))
			line_cut = NULL;
		else if (buf[i[1] + 1] == 0 &&
				(line_cut = create_line(buf, i[0], i[1], (char *)line_cut)))
			i[0] = i[1] + 2;
		i[1]++;
	}
	return (!lines) ? NULL : lines;
}

char	**end_of_file(char *buf, char **line, int ret)
{
	if (ret == 0)
	{
		if (create_lines(buf, 1) != NULL)
		{
			*line = create_lines(buf, 1)[0];
			return (0);
		}
		return (0);
	}
	buf[ret] = 0;
	return (line);
}

/*
** i[0] = count;
** i[1] = cpy;
*/

char	**reboot_variables(int *i, char **lines)
{
	if (i[1] == 1)
		free(lines);
	lines = (i[1] > 1) ? lines : NULL;
	i[1] = (i[1] > 1) ? i[1] - 1 : i[1];
	return (lines);
}

int		get_next_line(int fd, char **line)
{
	static int		i[2];
	int				ret;
	char			buf[BUFFER_SIZE + 1];
	static	char	**lines;

	lines = (!lines) ? NULL : lines;
	if (lines == NULL)
	{
		while (lines == NULL)
		{
			ret = read(fd, buf, BUFFER_SIZE);
			if (ret == -1 || BUFFER_SIZE == 0)
				return (-1);
			line = end_of_file(buf, line, ret);
			if (line == 0)
				return (0);
			lines = create_lines(buf, 0);
		}
		i[0] = count_lines(buf);
		i[1] = i[0];
	}
	*line = lines[i[0] - i[1]];
	lines = reboot_variables(i, lines);
	return (1);
}
