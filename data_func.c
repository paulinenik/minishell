#include "mshell.h"

t_data	*init_data(void)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	// if (data == NULL)
	// 	error
	data->bin = NULL;
	data->args = NULL;
	data->next = NULL;
	data->fd = init_fd();
	data->old_fd = init_fd();
	return (data);
}

void	add_data_front(t_data **old, t_data *new)
{
	if (*old == NULL)
	{
		*old = new;
		(*old)->next = NULL;
	}
	else if (old && new)
	{
		new->next = *old;
		*old = new;
	}
}

void	revert_data(t_data **data)
{
	t_data	*reversed;
	t_data	*next;
	int		size;

	reversed = NULL;
	size = data_size(*data);
	while ((*data) != NULL)
	{
		next = (*data)->next;
		add_data_front(&reversed, *data);
		(*data) = next;
		size--;
	}
	*data = reversed;
}

int	data_size(t_data *data)
{
	int	i;

	i = 0;
	while (data && i < 5)
	{
		data = data->next;
		i++;
	}
	return (i);
}

int	array_size(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	return (i);
}

char	**array_add_front(char **arr, char *str)
{
	char **new_array;
	int	i;

	i = 1;
	new_array = (char **)malloc(sizeof(char *) * (array_size(arr) + 2));
	// if (new_array == NULL)
	// 	malloc err
	new_array[0] = ft_strdup(str);
	while(arr[i - 1] != NULL)
	{
		new_array[i] = ft_strdup(arr[i - 1]);
		i++;
	}
	new_array[i] = NULL;
	return (new_array);
}