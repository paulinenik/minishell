#include "mshell.h"
#include "libft.h"
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void	set_shlvl(t_all *all)
{
	int	i;

	i = -1;
	while (all->env[++i])
	{
		if (!ft_strncmp(all->env[i], "SHLVL", 5))
		{
			all->shlvl = ft_atoi(ft_strchr(all->env[i], '=') + 1);
			all->shlvl++;
			free(all->env[i]);
			all->env[i] = ft_strdup("SHLVL=");
			all->env[i] = add_char(all->env[i], (all->shlvl + 48));
			all->env[i] = add_char(all->env[i], '"');
		}
	}
}

void	catch_sig(t_all *all)
{
	if (all->shlvl == 3)
	{
		signal(SIGQUIT, sigquit);
		signal(SIGINT, sigint);
	}
	else if (all->shlvl > 3)
	{
		signal(SIGINT, sigint2);
		signal(SIGQUIT, sigquit2);
	}
}

void	free_copy(char **copy, int i)
{
	while (--i >= 0)
		free(copy[i]);
	free(copy);
}

int	check_for_value(t_all *all, int	i, int	k)
{
	int	j;

	j = -1;
	if (k == -1)
	{
		while (all->env[i][++j])
			if (all->env[i][j] == '=')
				return (j);
		return (-1);
	}
	while (all->data->args[i][++j])
		if (all->data->args[i][j] == '=')
			return (j);
	return (-1);
}

void	help_dir(int i, char *str, t_all *all, char dir[1024])
{
	check_dir(str, all);
	getcwd(dir, 1024);
	while (dir[++i])
		;
	write(1, dir, i);
	write(1, "\n", 1);
}
