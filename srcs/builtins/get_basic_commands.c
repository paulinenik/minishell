/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_basic_commands.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 01:50:27 by jshondra          #+#    #+#             */
/*   Updated: 2021/05/20 18:13:16 by rgordon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mshell.h"
#include "libft.h"
#include <stdio.h>
#include <unistd.h>

int	get_pwd(void)
{
	char	dir[1024];

	getcwd(dir, 1024);
	printf("%s\n", dir);
	return (0);
}

int	get_export(t_all *all)
{
	if (all->data->args == NULL)
		print_export(all, -1, -1);
	else if (all->data->args != NULL)
		check_export(all, -1, -1, -1);
	return (0);
}

int	get_env(t_all *all)
{
	int	i;

	i = -1;
	if (all->data->args == NULL)
		print_env(all, i);
	else
	{
		while (all->data->args[++i])
		{
			if ((((all->data->args[i][0] == 0 || all->data->args[i] \
			 == NULL) && all->dola != 1) || (all->data->args[i] \
			  && all->dola != 1)) || (all->data->args[0][0] \
			   && all->dola == 1))
			{
				printf("env: %s: No such file or directory\n", \
				all->data->args[i]);
				return (127);
			}
		}
		i = 1;
		if (all->data->args[0][0] == 0 && all->dola == 1)
			print_env(all, i);
	}
	return (0);
}

int	get_cd(t_all *all)
{
	char	dir[1024];
	char	*key;

	key = NULL;
	getcwd(dir, 1024);
	if (all->data->args == NULL || all->data->args[0][0] == '~' \
	|| !ft_strncmp(all->data->args[0], "--", 3))
	{
		key = get_env_value(all->env, "HOME");
		if ((key == NULL || key[0] == 0) && all->data->args == NULL)
		{
			printf("minishell: cd: HOME not set\n");
			free(key);
			return (1);
		}
		else
			check_dir(all->home_path, all);
	}
	else if (!ft_strcmp(all->data->args[0], "-"))
		dir_back(all);
	else
		check_dir(all->data->args[0], all);
	free(key);
	return (g_exit_status[0]);
}

int	get_echo(t_all *all)
{
	int	i;

	i = -1;
	if (all->data->args == NULL)
		write(1, "\n", 2);
	else
	{
		if (!ft_strncmp(all->data->args[0], "-n", 3))
			i = 0;
		while (all->data->args[++i])
		{
			write(1, all->data->args[i], ft_strlen(all->data->args[i]));
			if (all->data->args[i + 1] != NULL)
				write(1, " ", 1);
		}
		if (ft_strncmp(all->data->args[0], "-n", 3))
			write(1, "\n", 1);
	}
	return (0);
}
