#include "mshell.h"

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

void	clear_all(t_data **data)
{
	t_data	*head;

	if (!data)
		return ;
	while (*data)
	{
		free((*data)->bin);
		(*data)->bin = NULL;
		td_array_clear((*data)->args);
		head = (*data);
		free(*data);
		(*data) = head->next;
		// write(1, "hello\n", 6);
	}
}