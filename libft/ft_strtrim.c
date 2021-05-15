/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 12:54:14 by jshondra          #+#    #+#             */
/*   Updated: 2021/05/15 16:00:56 by rgordon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check(char const *s1, char const *set)
{
	int	j;
	int	i;

	i = -1;
	while (s1[++i])
	{
		j = 0;
		while (set[j] && (set[j] != s1[i]))
			j++;
		if (s1[i] != set[j])
			break ;
	}
	return (i);
}

static int	check1(char const *s1, char const *set)
{
	int	j;
	int	n;

	n = ft_strlen(s1);
	while (--n > 0)
	{
		j = 0;
		while (set[j] && (set[j] != s1[n]))
			j++;
		if (s1[n] != set[j])
			break ;
	}
	return (n);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	int		n;
	char	*new;
	int		d;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	i = check(s1, set);
	if (!s1[i])
		return (new = ft_calloc(1, 1));
	d = i;
	n = check1(s1, set);
	new = malloc(n - i + 2);
	if (new != NULL)
	{
		j = 0;
		while (j <= n - i)
			new[j++] = s1[d++];
		new[j] = '\0';
	}
	return (new);
}
