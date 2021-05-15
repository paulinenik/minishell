#include "libft.h"

int	ft_scmp(const char *s1, const char *s2, char c)
{
	unsigned char	*str;
	unsigned char	*str2;
	size_t			i;

	str = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	if ((str == 0) && (str2 == 0))
		return (0);
	while ((str[i] || str2[i]) && str2[i] != c)
	{
		if (str[i] != str2[i])
			return (str[i] - str2[i]);
		i++;
	}
	return (0);
}
