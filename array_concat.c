#include "mshell.h"

void	array_concat(t_data *data, char **new_args)
{
	int	i;
	int j;
	size_t len;
	char	**reallocated;

	if (new_args == NULL)
		return ;
	i = 0;
	j = 0;
	len = array_size(data->args) + array_size(new_args) + 1;
	reallocated = (char **)malloc(sizeof(char *) * len);
	// if (reallocated == NULL)
	// 	malloc error
	while(data->args[i] != NULL)
	{
		reallocated[i] = data->args[i];
		i++;
	}
	while(new_args[j] != NULL)
	{
		reallocated[i + j] = new_args[j];
		j++;
	}
	reallocated[len - 1] = NULL;
	// while(len > 0)
	// {
	// 	printf("|%s|\n", reallocated[len - 1]);
	// 	len--;
	// }
	free(data->args);
	free(new_args);
	data->args = reallocated;
}