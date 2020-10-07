/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 15:24:19 by pcariou           #+#    #+#             */
/*   Updated: 2019/10/28 16:02:26 by pcariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	int	size;
	int len;
	char*new_s;

	len = 0;
	size = 0;
	new_s = (char *)s;
	while (new_s[len])
		len++;
	size = len;
	while (len >= 0)
	{
		if (new_s[len] == (char)c)
			return (&(new_s[len]));
		len--;
	}
	if (c == '\0')
		return (&(new_s[size]));
	return (0);
}
