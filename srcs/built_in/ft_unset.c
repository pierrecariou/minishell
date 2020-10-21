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

static void	ft_unset_one_var(char *arg, t_cmdv *cmdv)
{
	int i;

	i = -1;
	while (cmdv->envp[++i])
	{
		if (!ft_strncmp(arg, cmdv->envp[i], ft_strlen(arg)) &&
				cmdv->envp[i][ft_strlen(arg)] == '=')
		{
			free(cmdv->envp[i]);
			cmdv->envp[i] = cmdv->envp[i + 1];
			while (cmdv->envp[++i])
				cmdv->envp[i] = cmdv->envp[i + 1];
			break;
		}
	}
}

void		ft_unset(t_cmd cmd, t_cmdv *cmdv)
{
	int i;

	i = 0;
	while (cmd.argv[++i])
		ft_unset_one_var(cmd.argv[i], cmdv);
}
