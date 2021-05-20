/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 01:47:16 by jshondra          #+#    #+#             */
/*   Updated: 2021/05/20 18:33:40 by rgordon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mshell.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

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

void	dir_back(t_all *all)
{
	char	*str;
	char	dir[1024];
	int		i;

	i = -1;
	if (all->flag == -1)
	{
		printf("minishell: cd: OLDPWD not set\n");
		g_exit_status[0] = 1;
		return ;
	}
	else
	{
		str = get_env_value(all->env, "OLDPWD=");
		if (str[0] == 0)
		{
			printf("minishell: cd: OLDPWD not set\n");
			g_exit_status[0] = 1;
			free(str);
			return ;
		}
		help_dir(i, str, all, dir);
	}
}

void	change_env(char *s1, t_all *all, int k, char dir[1024])
{
	int	i;

	i = -1;
	if (k == 1)
	{
		while (all->env[++i])
		{
			if (!ft_strncmp("OLDPWD", all->env[i], 6))
			{
				free(all->env[i]);
				all->env[i] = ft_strdup(s1);
			}
		}
	}
	else
	{
		while (all->env[++i])
		{
			if (!ft_strncmp("PWD", all->env[i], 3))
			{
				free(all->env[i]);
				all->env[i] = ft_strdup(s1);
			}
		}
	}
}

void	check_dir(char	*str, t_all *all)
{
	char	dir[1024];
	char	*s1;
	int		i;

	getcwd(dir, 1024);
	if (chdir(str) == -1)
	{
		printf("minishell: cd: %s: No such file or directory\n", str);
		g_exit_status[0] = 1;
	}
	else
	{
		i = -1;
		s1 = ft_strjoin("OLDPWD=", dir);
		change_env(s1, all, 1, dir);
		free(s1);
		getcwd(dir, 1024);
		s1 = ft_strjoin("PWD=", dir);
		i = -1;
		change_env(s1, all, 0, dir);
		free(s1);
		all->flag++;
		g_exit_status[0] = 0;
	}
}
