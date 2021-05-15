/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 11:54:45 by jshondra          #+#    #+#             */
/*   Updated: 2021/05/15 16:14:30 by rgordon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*plus(int n, int l)
{
	int		nbr;
	char	*str;

	nbr = n;
	while (n != 0)
	{
		l++;
		n /= 10;
	}
	str = (char *)malloc(l + 1);
	if (str == NULL)
		return (NULL);
	str[l] = '\0';
	l--;
	while (nbr != 0)
	{
		str[l] = (nbr % 10) + 48;
		nbr /= 10;
		l--;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	int		l;
	char	*str;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	l = 0;
	if (n == 0)
		return (ft_strdup("0"));
	if (n < 0)
	{
		l = 1;
		n *= -1;
	}
	str = plus(n, l);
	if (str == NULL)
		return (NULL);
	if (l == 1)
		str[0] = '-';
	return (str);
}
