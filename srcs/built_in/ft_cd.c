/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grezette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 18:19:20 by grezette          #+#    #+#             */
/*   Updated: 2020/10/20 15:16:36 by pcariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//Attention, ca leaks si ft_cd est appelé une seconde fois ou plus.

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

static int		ft_half_pwd(char **envp, char *str)
{
	char	*src;
	int		fctr;

	fctr = 4096 - ft_strlen(str);
	if (!(src = (char *)malloc(sizeof(char *) * (fctr + ft_strlen(str)))))
		return (-1);
	while (!(getcwd(src + 4, fctr)))
	{
		free(src);
		fctr *= 2;
		if (!(src = (char *)malloc(sizeof(char *) * (fctr + ft_strlen(str)))))
			return (-1);
	}
	fctr = -1;
	while (str[++fctr])
		src[fctr] = str[fctr];
	fctr = 0;
	while (ft_strncmp(envp[fctr], str, ft_strlen(str) - 1))
		fctr++;
	envp[fctr] = src;
	return (0);
}

int		ft_cd(t_cmd cmd, t_cmdv *cmdv)
{
	//	if (ft_half_pwd(cmdv->envp, "OLDPWD="))
	//		return (-1);

	int i;

	i = 0;
	while (ft_strncmp(cmdv->envp[i], "HOME=", 4))
		i++;
	if (!cmd.argv[1])
		chdir(cmdv->envp[i] + 5);
	else if (chdir(cmd.argv[1]))
	{
		ft_putstr_fd("cd: ", 1);
		ft_putstr_fd(cmd.argv[1], 1);
		ft_putstr_fd(": No such file or directory\n", 1);
	}
	else
		if (ft_half_pwd(cmdv->envp, "PWD="))
			return (-1);
	return (0);
}
