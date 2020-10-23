/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <pcariou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 19:11:58 by pcariou           #+#    #+#             */
/*   Updated: 2020/10/23 19:22:05 by pcariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	quotes_not_closed(char *buf)
{
	int i;
	int inquotes_d;
	int inquotes_s;

	i = -1;
	inquotes_d = 0;
	inquotes_s = 0;
	while (buf[++i])
	{
		if (inquotes_d == 0 && buf[i] == '\"' && inquotes_s == 0)
			inquotes_d = 1;
		else if (inquotes_s == 0 && buf[i] == '\'' && inquotes_d == 0)
			inquotes_s = 1;
		else if (buf[i] == '\"' && inquotes_s == 0)
			inquotes_d = 0;
		else if (buf[i] == '\'' && inquotes_d == 0)
			inquotes_s = 0;
	}
	if (inquotes_s != 0 || inquotes_d != 0)
		return (1);
	return (0);
}
