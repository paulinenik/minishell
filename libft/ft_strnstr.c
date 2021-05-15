/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 15:26:52 by jshondra          #+#    #+#             */
/*   Updated: 2021/05/15 16:02:25 by rgordon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *sub, size_t len)
{
	size_t	i;
	size_t	k;

	k = 0;
	if (!s1 && !sub)
		return (NULL);
	i = ft_strlen(sub);
	if (i == 0)
		return ((char *)s1);
	if (len)
	{
		while (s1[k] && k < len - i + 1)
		{
			if (ft_strncmp(&s1[k], sub, i) == 0)
				return ((char *)(s1 + k));
			k++;
		}
	}
	return (NULL);
}
