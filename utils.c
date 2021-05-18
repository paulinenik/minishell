/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshondra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 01:47:16 by jshondra          #+#    #+#             */
/*   Updated: 2021/05/18 01:47:18 by jshondra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	dir_back(t_all *all)
{
	char	*str;
	char	dir[1024];
	int 	i;

	i = -1;
	if (all->flag == -1)
	{
		printf("minishell: cd: OLDPWD not set\n");
		return ;
	}
	else
	{
		str = get_env_value(all->env, "OLDPWD");
		check_dir(str, all);
		getcwd(dir, 1024);
		while(dir[++i])
			;
		write(1, dir, i);
		write(1, "\n", 1);
	}
}

void	change_env(char *s1, t_all *all, int k, char dir[1024])
{
	int	i;

	i = -1;
	if (k == 1)
	{
		while (all->env[++i])
			if (!ft_strncmp("OLDPWD", all->env[i], 6))
			{
				free(all->env[i]);
				all->env[i] = ft_strdup(s1);
			}
	}
	else
	{
		while (all->env[++i])
			if (!ft_strncmp("PWD", all->env[i], 3))
			{
				free(all->env[i]);
				all->env[i] = ft_strdup(s1);
			}
	}
}

void	check_dir(char	*str, t_all *all)
{
	char	dir[1024];
	char	*s1;

	getcwd(dir, 1024);
	if (chdir(str) == -1)
	{
		printf("minishell: cd: %s: No such file or directory\n", str);
		g_exit_status[0] = 1;
	}
	else
	{
		int i = -1;
		s1 = ft_strjoin("OLDPWD=", dir);
		change_env(s1, all, 1, dir);
		free(s1);
		getcwd(dir, 1024);
		s1 = ft_strjoin("export PWD=", dir);
		i = -1;
		change_env(s1, all, 0, dir);
		free(s1);
		g_exit_status[0] = 1;
		all->flag++;
	}
}


void	free_copy(char **copy, int i)
{
	while (--i >= 0)
		free(copy[i]);
	free(copy);
}
