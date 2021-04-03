/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshondra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 16:20:24 by jshondra          #+#    #+#             */
/*   Updated: 2020/11/04 18:48:04 by jshondra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *rest, const void *restsrc, size_t n)
{
	char			*str;
	char			*str2;
	size_t			i;

	str = rest;
	str2 = (char*)restsrc;
	i = 0;
	if (rest == NULL && restsrc == NULL)
		return (NULL);
	while (i < n)
	{
		str[i] = str2[i];
		i++;
	}
	return (rest);
}
