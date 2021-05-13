#include "mshell.h"

char	**alph_sort(char	**copy, int	n)
{
	int		j;
	int		i;
	char	*tmp;

	i = -1;
	tmp = NULL;
	while (++i < n)
	{
		j = i + 1;
		while (j < n)
		{
			if (ft_strcmp(copy[i], copy[j]) > 0)
			{
				tmp = copy[i];
				copy[i] = copy[j];
				copy[j] = tmp;
			}
			j++;
		}
	}
	return (copy);
}

int	save_index(t_data *data, char	**envp)
{
	int	i;
	int	j;
	int	k;

	i = -1;
	j = -1;
	k = 0;
	while (data->args[++i])
	{
		j = -1;
		while (envp[++j])
		{
			if (!ft_strcmp(envp[j], data->args[i]))
			{
				k++;
				break ;
			}
		}
	}
	return (k);
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

void	check_dir(char	*str)
{
	if (chdir(str) == -1)
		printf("minishell: cd: %s: No such file or directory\n", str);
}