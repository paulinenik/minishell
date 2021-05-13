#include "mshell.h"

int	help_search(char **str, int i, int temp)
{
	while (str[i][++temp])
	{
		if (str[i][temp] == '=')
			break ;
		if (ft_isalnum(str[i][temp]) == 0)
		{
			temp = -2;
			break ;
		}
	}
	return (temp);
}

int	alnum_search(char **str, int i, int temp, int s)
{
	temp = help_search(str, i, temp);
	if ((str[i][0] == '=') || (temp != -2 && str[i][temp] == '=' && s == -1)
	|| str[i][0] == 0)
		temp = -2;
	if (((str[i][0] <= '9' && str[i][0] >= '0')
	|| temp == -2) && (s < 0))
	{
		write(1, "minishell: ", 12);
		if (s < 0 && s == -2)
			write(1, "export: `", 10);
		else
			write(1, "unset: `", 9);
		write(1, str[i], ft_strlen(str[i]));
		write(1, "': not a valid identifier\n", 27);
		return (0);
	}
	return (-1);
}
