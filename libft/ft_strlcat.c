/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshondra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 14:51:41 by jshondra          #+#    #+#             */
/*   Updated: 2020/11/05 14:51:58 by jshondra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t		i;
	size_t		n;
	size_t		k;

	if (!dst && !src)
		return (0);
	k = ft_strlen(dst);
	i = 0;
	if (size <= k)
		return (ft_strlen(src) + size);
	n = ft_strlen(dst);
	if (size != 0)
	{
		while (i < ((size - 1 - k)) && (src[i]))
		{
			dst[n] = src[i];
			i++;
			n++;
		}
		dst[n] = '\0';
	}
	return (ft_strlen(src) + k);
}
