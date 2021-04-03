/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshondra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 21:57:15 by jshondra          #+#    #+#             */
/*   Updated: 2020/11/06 14:21:31 by jshondra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	char			*str;
	char			*str2;
	size_t			i;

	if ((!dst) || (!src))
		return (0);
	str = dst;
	str2 = (char*)src;
	i = 0;
	if (size != 0)
	{
		while ((i < size - 1) && (str2[i]))
		{
			str[i] = str2[i];
			i++;
		}
		str[i] = '\0';
	}
	return (ft_strlen(str2));
}
