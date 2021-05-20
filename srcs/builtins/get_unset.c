/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 01:49:41 by jshondra          #+#    #+#             */
/*   Updated: 2021/05/20 18:15:06 by rgordon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mshell.h"
#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

char	**unseter(t_all *all, int	i, int	j, char	**copy)
{
	int	k;

	k = 0;
	while (all->data->args[++i])
	{
		j = -1;
		while (all->env[++j])
		{
			if (!ft_strcmp(all->env[j], all->data->args[i])
				|| (ft_strncmp(all->data->args[i], all->env[j], \
					ft_strlen(all->data->args[i]) + 1) == 61))
			{
				k++;
				break ;
			}
		}
		alnum_search(all->data->args, i, -1, -1);
	}
	i = -1;
	while (all->env[++i])
		;
	copy = malloc ((i + 1 - k) * sizeof(char *));
	copy[i - k] = NULL;
	return (copy);
}

char	**help_unset(t_all *all, int	*f, int	i, char	**copy)
{
	copy[*f] = ft_strdup(all->env[i]);
	(*f)++;
	return (copy);
}

char	**unset_errors(t_all *all, int	i, int	j, char	**copy)
{
	int	k;
	int	f;

	f = 0;
	k = 1;
	while (all->env[++i])
	{
		j = -1;
		while (all->data->args[++j])
		{
			if (check_for_value(all, j, 0) != -1)
				continue ;
			k = (ft_strcmp(all->env[i], all->data->args[j]));
			if (!ft_scmp(all->data->args[j], all->env[i], '=')
				&& (ft_strncmp(all->data->args[j], all->env[i], \
				ft_strlen(all->env[j]) + 1) == -61))
				k = 0;
			if (k == 0)
				break ;
		}
		if (k != 0)
			help_unset(all, &f, i, copy);
	}
	copy[f] = NULL;
	return (copy);
}

int	get_unset(t_all *all)
{
	int		j;
	char	**copy;

	j = -1;
	copy = NULL;
	if (ft_strncmp(all->data->bin, "unset", 6))
		return (1);
	if ((all->data->args != NULL))
	{
		copy = unseter(all, -1, -1, copy);
		unset_errors(all, -1, -1, copy);
		while (all->env[++j])
			;
		while (--j >= 0)
			free(all->env[j]);
		free(all->env);
		all->env = copy;
	}
	return (0);
}

int	get_exit(t_all *all)
{
	int	i;

	i = -1;
	write(1, "exit\n", 5);
	exit_code(all);
	while (all->data->args[0][++i])
	{
		if (ft_isalpha(all->data->args[0][i]))
		{
			printf("exit: %s: numeric argument required\n", \
			all->data->args[0]);
			exit(255);
		}
	}
	return (0);
}
