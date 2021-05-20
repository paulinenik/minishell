/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_cap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 01:49:12 by jshondra          #+#    #+#             */
/*   Updated: 2021/05/20 18:25:24 by rgordon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mshell.h"
#include "libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <term.h>

char	*selector_cap(char *input, int *i, char buf[101], t_all *all)
{
	if (!ft_strncmp(buf, "\e[A", 4))
		input = arrow_up(input, all, i, -1);
	else if (!ft_strncmp(buf, "\e[B", 4))
		input = arrow_down(input, all, i, -1);
	else if (!ft_strncmp(buf, "\177", 2))
		input = delete_symbol(input, i);
	else if (!ft_strncmp(buf, "\e[D", 4))
		input = move_left(input, i);
	else if (!ft_strncmp(buf, "\e[C", 4))
		input = move_right(input, i);
	else if (!ft_strncmp(buf, "\3", 2))
		input = control_c(input, buf);
	else if (!ft_strncmp(buf, "\t", 2))
		;
	else
		input = usual_cap(input, i, buf);
	return (input);
}

char	*select_cap(t_all *all, char *input, struct termios term, \
struct termios term1)
{
	int		i;
	int		l;
	char	buf[101];

	i = 0;
	while (ft_strncmp(buf, "\n", 1))
	{
		l = read(0, buf, 100);
		buf[l] = 0;
		if (!ft_strncmp(buf, "\4", 2))
			ctrl_d(term, term1, input);
		else
			input = selector_cap(input, &i, buf, all);
	}
	return (input);
}

char	*delete_symbol(char *input, int *i)
{
	if (*i > 0)
	{
		tputs(cursor_left, 1, ft_putchar);
		tputs(tgetstr("dc", 0), 1, ft_putchar);
		input = delete_char(input);
		(*i)--;
	}
	return (input);
}

char	*arrow_down(char *input, t_all *all, int *i, int l)
{
	tputs(restore_cursor, 1, ft_putchar);
	while (--(*i) >= 0)
		tputs(tgetstr("dc", 0), 1, ft_putchar);
	if (all->commands_hist != NULL && all->commands_hist[all->size])
	{
		if (all->commands_hist[all->size])
			write(1, all->commands_hist[all->size], \
			ft_strlen(all->commands_hist[all->size]));
		(*i) = ft_strlen(all->commands_hist[all->size]);
		if (input != NULL)
			free(input);
		input = NULL;
		while (all->commands_hist[all->size][++l])
			input = add_char(input, all->commands_hist[all->size][l]);
		all->size++;
	}
	else if (input != NULL)
	{
		free(input);
		input = NULL;
	}
	return (input);
}

char	*arrow_up(char *input, t_all *all, int *i, int l)
{
	tputs(restore_cursor, 1, ft_putchar);
	while (--(*i) > 0)
		tputs(tgetstr("dc", 0), 1, ft_putchar);
	if (all->commands_hist != NULL)
	{
		if (all->size > 0)
			all->size--;
		write(1, all->commands_hist[all->size], \
		ft_strlen(all->commands_hist[all->size]));
		(*i) = ft_strlen(all->commands_hist[all->size]);
		if (input != NULL)
			free(input);
		input = NULL;
		while (all->commands_hist[all->size][++l])
			input = add_char(input, all->commands_hist[all->size][l]);
	}
	return (input);
}
