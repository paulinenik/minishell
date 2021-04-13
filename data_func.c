#include "mshell.h"

void	add_data_front(t_data **old, t_data *new)
{
	if (old && new)
	{
		new->next = *old;
		*old = new;
	}
}

void	revert_data(t_data **data)
{
	t_data	*reversed;
	t_data	*next;

	reversed = NULL;
	while(data)
	{
		add_data_front(&reversed, *data);
		printf("this go free while reverse %s\n", (*data)->bin);
		free((*data)->bin);
		(*data)->bin = NULL;
		td_array_clear((*data)->args);
		next = (*data)->next;
		free(*data);
		(*data) = next;
	}
	*data = next;
}

int		data_size(t_data *data)
{
	int i;

	i = 0;
	while (data)
	{
		data = data->next;
		i++;
	}
	return (i);
}