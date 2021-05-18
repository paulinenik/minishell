/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_caps.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshondra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 01:47:33 by jshondra          #+#    #+#             */
/*   Updated: 2021/05/18 01:49:23 by jshondra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mshell.h"

char	*move_right(char *input, int *i)
{
	if (*i < (int)ft_strlen(input))
	{
		tputs(cursor_right, 1, ft_putchar);
		(*i)++;
	}
	return (input);
}

char	*move_left(char *input, int *i)
{
	if (*i > 0)
	{
		tputs(cursor_left, 1, ft_putchar);
		(*i)--;
	}
	return (input);
}

void	ctrl_d(struct	termios	term, struct termios term1, char *input)
{
	if (input == NULL)
	{
		write (1, "exit\n", 6);
		term = term1;
		tcsetattr(0, TCSANOW, &term);
		exit (0);
	}
}

char	*control_c(char *input, char buf[101])
{
	buf[0] = '\n';
	write(1, "\n", 1);
	input = add_char(input, '\n');
	return (input);
}

char	*usual_cap(char *input, int *i, char buf[101])
{
	if (*buf != '\n')
		input = add_char(input, *buf);
	write (1, buf, 1);
	(*i)++;
	return (input);
}
