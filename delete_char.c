#include "mshell.h"

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
		return (NULL);
	ft_memcpy(reallocated, str, str_len - 1);
	reallocated[str_len - 1] = '\0';
	free(str);
	return (reallocated);
}
