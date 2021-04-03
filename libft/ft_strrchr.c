/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshondra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 15:02:52 by jshondra          #+#    #+#             */
/*   Updated: 2020/11/04 19:14:52 by jshondra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*str;
	int		i;

	i = 0;
	str = (char*)s;
	while (*str)
	{
		str++;
		i++;
	}
	if (c == '\0')
		return (str);
	str--;
	while (i > 0)
	{
		if (*str == c)
			return (str);
		str--;
		i--;
	}
	return (NULL);
}
