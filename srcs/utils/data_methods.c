#include "mshell.h"
#include "libft.h"
#include <stdlib.h>
#include <errno.h>

t_data	*init_data(void)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (data == NULL)
		exit(ENOMEM);
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

int	*init_fd(void)
{
	int	*fds;

	fds = (int *)malloc(sizeof(int) * 2);
	if (fds == NULL)
		exit(ENOMEM);
	fds[0] = 0;
	fds[1] = 1;
	return (fds);
}
