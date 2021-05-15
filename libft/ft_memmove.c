/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 18:34:58 by jshondra          #+#    #+#             */
/*   Updated: 2021/05/15 16:12:16 by rgordon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char			*str;
	char			*str2;
	size_t			i;

	str = (char *)dst;
	str2 = (char *)src;
	i = -1;
	if (!dst && !src)
		return (NULL);
	if (len < 1 && dst == src)
		return (dst);
	if (str < str2)
	{
		while (++i < len)
			str[i] = str2[i];
	}
	else if (str > str2)
	{
		i = len;
		i++;
		while (--i > 0)
			str[i - 1] = str2[i - 1];
	}
	return (dst);
}
