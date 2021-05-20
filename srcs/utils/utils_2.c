/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 01:47:24 by jshondra          #+#    #+#             */
/*   Updated: 2021/05/20 18:31:25 by rgordon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mshell.h"
#include "libft.h"
#include <unistd.h>
#include <stdlib.h>

int	help_search(char **str, int i, int temp)
{
	while (str[i][++temp])
	{
		if (str[i][temp] == '=')
			break ;
		if (ft_isalnum(str[i][temp]) == 0)
		{
			temp = -2;
			break ;
		}
	}
	return (temp);
}

int	alnum_search(char **str, int i, int temp, int s)
{
	temp = help_search(str, i, temp);
	if ((str[i][0] == '=') || (temp != -2 && str[i][temp] == '=' && s == -1)
	|| str[i][0] == 0)
		temp = -2;
	if (((str[i][0] <= '9' && str[i][0] >= '0')
	|| temp == -2) && (s < 0))
	{
		write(1, "minishell: ", 12);
		if (s < 0 && s == -2)
			write(1, "export: `", 10);
		else
			write(1, "unset: `", 9);
		write(1, str[i], ft_strlen(str[i]));
		write(1, "': not a valid identifier\n", 27);
		g_exit_status[0] = 1;
		return (0);
	}
	return (-1);
}

void	print_env(t_all *all, int i)
{
	while (all->env[++i])
		if (check_for_value(all, i, -1) != -1)
			printf("%s\n", all->env[i]);
}

void	exit_code(t_all *all)
{
	if (all->data->args == NULL)
		exit(0);
	else if (!ft_strcmp(all->data->args[0], "0"))
		exit(0);
	else if (!ft_strcmp(all->data->args[0], "1"))
		exit(1);
	else if (!ft_strcmp(all->data->args[0], "-1"))
		exit(255);
	else if (!ft_strcmp(all->data->args[0], "999999"))
		exit(63);
	else if (!ft_strcmp(all->data->args[0], "-999999"))
		exit(193);
	else
		exit(ft_atoi(all->data->args[0]));
}

void	set_oldpwd(t_all *all)
{
	int		i;
	char	**copy;

	i = -1;
	copy = init(all->env, 1);
	while (all->env[++i])
		;
	copy[i] = ft_strdup("OLDPWD");
	copy[i + 1] = NULL;
	td_array_clear(all->env);
	all->env = copy;
}
