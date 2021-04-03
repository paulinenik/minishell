/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshondra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 17:09:29 by jshondra          #+#    #+#             */
/*   Updated: 2020/11/04 18:51:37 by jshondra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	cut(int *n, int fd)
{
	if (*n == -2147483648)
	{
		write(fd, "-2147483648", 11);
	}
}

void	put(int *n, int *b, int fd)
{
	if ((*n < 0) && (*n != -2147483648))
	{
		write(fd, "-", 1);
		*n *= -1;
		*b *= -1;
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	int		l;
	int		v;
	char	c;

	l = 1;
	v = n;
	put(&v, &n, fd);
	if (!fd)
		return ;
	while ((v = v / 10) > 0)
		l *= 10;
	while (l > 0)
	{
		cut(&n, fd);
		if (n == -2147483648)
			break ;
		v = n / l;
		c = v + 48;
		write(fd, &c, 1);
		if (v % l == 0)
			v = v / l;
		else
			n = n % l;
		l /= 10;
	}
}
