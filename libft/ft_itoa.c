/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 11:54:45 by jshondra          #+#    #+#             */
/*   Updated: 2021/04/08 20:31:24 by rgordon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*plus(int n, int l)
{
	int		nbr;
	// int		k;
	char	*str;

	// k = l;
	nbr = n;
	while (n != 0)
	{
		l++;
		n /= 10;
	}
	if ((str = (char *)malloc(l + 1)) == NULL)
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

char			*ft_itoa(int n)
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
	if ((str = plus(n, l)) == NULL)
		return (NULL);
	if (l == 1)
		str[0] = '-';
	return (str);
}
