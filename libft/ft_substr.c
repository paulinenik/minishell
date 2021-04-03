/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshondra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 16:54:37 by jshondra          #+#    #+#             */
/*   Updated: 2020/11/04 19:16:36 by jshondra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;
	size_t	n;

	n = start;
	i = start;
	if (!s)
		return (NULL);
	if (n >= ft_strlen(s))
		return (ft_strdup(""));
	while (s[n + 1])
		n++;
	if ((str = malloc(len + 1)) != NULL)
	{
		n = 0;
		while ((len > 0) && (s[i]))
		{
			str[n] = s[i];
			i++;
			n++;
			len--;
		}
		str[n] = '\0';
	}
	return (str);
}
