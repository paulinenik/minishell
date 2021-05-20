#include "mshell.h"
#include <stdlib.h>

void	td_array_clear(char **arr)
{
	int	i;

	i = 0;
	if (arr == NULL)
		return ;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
	arr = NULL;
}

void	clear_data(t_data **data)
{
	t_data	*head;

	if (!data)
		return ;
	while (*data != NULL)
	{
		free((*data)->bin);
		(*data)->bin = NULL;
		td_array_clear((*data)->args);
		free((*data)->fd);
		(*data)->fd = NULL;
		free((*data)->old_fd);
		(*data)->old_fd = NULL;
		head = (*data)->next;
		free(*data);
		(*data) = head;
	}
}

void	stop_parse(char **input, int error_code)
{
	**input = '\0';
	g_exit_status[0] = error_code;
}
