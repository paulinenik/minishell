/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 19:08:02 by jshondra          #+#    #+#             */
/*   Updated: 2021/05/15 16:04:02 by rgordon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*str;
	int		n;

	if ((!s1) || (!s2))
		return (NULL);
	i = ft_strlen(s1);
	n = ft_strlen(s2);
	j = 0;
	str = malloc(n + i + 1);
	if (str != NULL)
	{
		while (i > 0)
		{
			str[j] = s1[j];
			j++;
			i--;
		}
		i = -1;
		while (++i < n)
			str[j++] = s2[i];
		str[j] = '\0';
	}
	return (str);
}
