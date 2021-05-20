#include "mshell.h"
#include "libft.h"
#include <stdio.h>
#include <errno.h>

char	*delete_char(char *str)
{
	char	*reallocated;
	size_t	str_len;

	if (str == NULL || ft_strlen(str) == 0)
		return (ft_strdup(""));
	else
		str_len = ft_strlen(str);
	reallocated = (char *)malloc(sizeof(char) * str_len);
	if (reallocated == NULL)
		exit(ENOMEM);
	ft_memcpy(reallocated, str, str_len - 1);
	reallocated[str_len - 1] = '\0';
	free(str);
	return (reallocated);
}

char	*add_char(char *str, char c)
{
	char	*reallocated;
	size_t	str_len;

	if (str == NULL)
		str_len = 0;
	else
		str_len = ft_strlen(str);
	reallocated = (char *)malloc(sizeof(char) * str_len + 2);
	if (reallocated == NULL)
		exit(ENOMEM);
	ft_memcpy(reallocated, str, str_len);
	reallocated[str_len] = c;
	reallocated[str_len + 1] = '\0';
	free(str);
	return (reallocated);
}

char	*null_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	str = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!str)
		return (NULL);
	while (s1 && s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2 && s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}
