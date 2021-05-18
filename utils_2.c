/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshondra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 01:47:24 by jshondra          #+#    #+#             */
/*   Updated: 2021/05/18 01:47:26 by jshondra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mshell.h"

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
