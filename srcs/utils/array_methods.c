#include "mshell.h"
#include "libft.h"
#include <stdlib.h>
#include <errno.h>

void	array_concat(t_data *data, char **new_args)
{
	int		i;
	int		common_len;
	int		arg_len;
	char	**reallocated;

	if (new_args == NULL)
		return ;
	i = 0;
	arg_len = array_size(data->args);
	common_len = arg_len + array_size(new_args) + 1;
	reallocated = (char **)malloc(sizeof(char *) * common_len);
	if (reallocated == NULL)
		exit(ENOMEM);
	ft_memcpy(reallocated, data->args, sizeof(char *) * (arg_len));
	while (new_args[i] != NULL)
	{
		reallocated[i + arg_len] = new_args[i];
		i++;
	}
	reallocated[common_len - 1] = NULL;
	free(data->args);
	free(new_args);
	data->args = reallocated;
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
	char	**new_array;
	int		i;

	i = 1;
	if (!(ft_strncmp(arr[0], ".", 2)))
		return (arr);
	new_array = (char **)malloc(sizeof(char *) * (array_size(arr) + 2));
	if (new_array == NULL)
		exit(ENOMEM);
	new_array[0] = ft_strdup(str);
	while (arr[i - 1] != NULL)
	{
		new_array[i] = ft_strdup(arr[i - 1]);
		i++;
	}
	new_array[i] = NULL;
	return (new_array);
}

char	**list_to_array(t_list *list)
{
	char	**array;
	t_list	*head;
	int		list_size;
	int		i;

	i = 0;
	head = list;
	if (list == NULL)
		return (NULL);
	list_size = ft_lstsize(list);
	array = (char **)malloc(sizeof(char *) * (list_size + 1));
	if (array == NULL)
		exit(ENOMEM);
	while (i < list_size)
	{
		array[i] = ft_strdup(list->content);
		i++;
		list = list->next;
	}
	array[i] = NULL;
	ft_lstclear(&head, &free);
	return (array);
}
