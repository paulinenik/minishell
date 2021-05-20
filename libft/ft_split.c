/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 16:44:05 by jshondra          #+#    #+#             */
/*   Updated: 2021/05/20 18:03:30 by rgordon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	crt(char const *s, char c)
{
	int	i;
	int	k;
	int	words;

	words = 0;
	k = 0;
	i = -1;
	while (s[++i])
	{
		if (s[i] == c)
			k = 0;
		else if (k == 0)
		{
			words++;
			k = 1;
		}
	}
	return (words);
}

static int	count(char const *s, char c)
{
	int	i;
	int	symbols;

	i = 0;
	symbols = 0;
	while (s[i] == c && s[i])
		i++;
	while (s[i] != c && s[i])
	{
		i++;
		symbols++;
	}
	return (symbols);
}

static char	**cut(char **new, int i)
{
	int	j;

	j = -1;
	while (++j < i)
		free(new[j]);
	free(new);
	return (NULL);
}

char const	*helper(char const *s, char c)
{
	while (*s == c && *s)
		s++;
	return (s);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		nbr;
	char	**new;

	if (!s)
		return (NULL);
	i = -1;
	j = -1;
	new = ft_calloc(crt(s, c) + 1, sizeof(char *));
	if (new != NULL)
	{
		while (++i < crt(s, c))
		{
			nbr = count(s, c);
			new[i] = (ft_calloc(nbr + 1, 1));
			if (new[i] == NULL)
				return (new = cut(new, i));
			s = helper(s, c);
			while (++j < nbr)
				new[i][j] = *s++;
			j = -1;
		}
	}
	return (new);
}
