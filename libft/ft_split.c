/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshondra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 16:44:05 by jshondra          #+#    #+#             */
/*   Updated: 2020/11/05 15:18:18 by jshondra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		crt(char const *s, char c)
{
	int i;
	int k;
	int words;

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

static int		count(char const *s, char c)
{
	int i;
	int symbols;

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

static char		**cut(char **new, int i)
{
	int j;

	j = -1;
	while (++j < i)
		free(new[j]);
	free(new);
	return (NULL);
}

char			**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		k;
	int		nbr;
	char	**new;

	if (!s)
		return (NULL);
	i = -1;
	j = -1;
	k = crt(s, c);
	if ((new = ft_calloc(k + 1, sizeof(char *))) != NULL)
		while (++i < k)
		{
			nbr = count(s, c);
			if ((new[i] = (ft_calloc(nbr + 1, 1))) == NULL)
				return (new = cut(new, i));
			while (*s == c && *s)
				s++;
			while (++j < nbr)
				new[i][j] = *s++;
			j = -1;
		}
	return (new);
}
