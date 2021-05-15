/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 16:40:03 by jshondra          #+#    #+#             */
/*   Updated: 2021/05/14 22:08:41 by rgordon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *c)
{
	int		i;
	char	*src;

	i = 0;
	if (c == NULL)
		return (NULL);
	while (c[i])
		i++;
	if ((src = ft_calloc(i + 1, 1)) != NULL)
	{
		i = 0;
		while (c[i])
		{
			src[i] = c[i];
			i++;
		}
	}
	return (src);
}
