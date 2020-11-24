/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grezette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 16:18:47 by grezette          #+#    #+#             */
/*   Updated: 2020/11/24 15:51:23 by pcariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_strncmp(char *s1, char *s2, size_t n)
{
	size_t i;

	i = 0;
	if (n == 0)
		return (0);
	while (i < n - 1 && s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*ft_get_pwd(t_cmdv *cmdv)
{
	int		fctr;
	char	*src;

	fctr = 0;
	while (cmdv->envp[fctr] &&
		ft_strncmp(cmdv->envp[fctr], "PWD=", ft_strlen("PWD=") - 1))
		fctr++;
	if (fctr != (int)ft_square_strlen(cmdv->envp))
	{
		ft_putstr_fd(&cmdv->envp[fctr][4], 1);
		return (NULL);
	}
	fctr = 4096;
	if (!(src = (char *)malloc(sizeof(char *) * (fctr))))
		return (NULL);
	if (!(getcwd(src, fctr)))
		return (NULL);
	return (src);
}

int		ft_pwd(t_cmd cmd, t_cmdv *cmdv)
{
	char	*src;

	(void)cmd;
	src = ft_get_pwd(cmdv);
	if (src)
		ft_putstr_fd(src, 1);
	free(src);
	write(1, "\n", 1);
	return (0);
}
