#include "mshell.h"

void	parse(char *input, t_all *all)
{
	if (ft_strlen(input) == 1)
		return ;
	all->data = init_data();
	all->data->bin = init_exec_name(&input, all->env);
	// printf("|%s| %zu - input\n", input, ft_strlen(input));
	printf("%s - binary name\n", all->data->bin);
	while (*input != '\0')
	{
		if (*input == ' ')
		{
			if (all->data->args == NULL)
				all->data->args = get_args(&input, all->env);
			else
				array_concat(all->data, get_args(&input, all->env));
		}
		else if (ft_strchr("|><;", *input) != NULL)
			check_specchar(&input, all);
		else
			input++;
	}
	if (all->data->bin)
		to_process(all);
}

void	check_specchar(char **input, t_all *all)
{
	t_data	*next_data;

	if (**input == ';')
	{
		to_process(all);
		clear_all(&all->data);
		all->data = init_data();
		(*input)++;
		all->data->bin = init_exec_name(input, all->env);
	}
	else if (**input == '|')
	{
		next_data = init_data();
		(*input)++;
		next_data->bin = init_exec_name(input, all->env);
		add_data_front(&all->data, next_data);
	}
	else
	{
		redirect_parse(input, all);
		// array_concat(all->data, get_args(input, all->env));
	}
		//продолжить парсить аргументы
		//соединить массивы
}

char	**get_args(char **input, char **envp)
{
	char	**args;
	char	*content;
	t_list	*item;
	t_list	*list;

	args = NULL;
	content = NULL;
	list = NULL;
	write(1, "hello\n", 6);
	while (**input == ' ')
		(*input)++;
	while (**input != '\0' && **input != ';' && **input != '|' && **input != '\n' && **input != '>' && **input != '<')
	{
		content = init_exec_name(input, envp);
		item = ft_lstnew(content);
		if (item == NULL)
			exit(0);
		ft_lstadd_back(&list, item);
		if (**input == ' ')
			(*input)++;
	}
	args = list_to_array(list);
	return (args);
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
		exit(0);
	while (i < list_size)
	{
		array[i] = ft_strdup(list->content);
		// free(list->content);
		// list->content = NULL;
		i++;
		list = list->next;
	}
	array[i] = NULL;
	// while (i >= 0)
	// {
	// 	printf("%s - arg[%d]\n", array[i], i);
	// 	i--;
	// }
	ft_lstclear(&head, &free);
	return (array);
}

char	*add_char(char *str, char c)
{
	char	*reallocated;
	size_t	str_len;

	if (str == NULL)
		str_len = 0;
	else
		str_len = ft_strlen(str);
	reallocated = (char *)malloc(sizeof(char) * str_len + 2);
	if (reallocated == NULL)
		return (NULL);
	ft_memcpy(reallocated, str, str_len);
	reallocated[str_len] = c;
	reallocated[str_len + 1] = '\0';
	free(str);
	return (reallocated);
}

char	*init_exec_name(char **input, char **envp)
{
	char	*result;

	result = NULL;
	while (**input == ' ')
		(*input)++;
	while (**input != '\0' && **input != ' ' && **input != ';' && **input != '|' && **input != '\n')
	{
		if (**input == 39)
			result = single_qoutation(input, result);
		else if (**input == 34)
			result = double_quotation(input, envp, result);
		else if (**input == 36)
			result = get_envp(input, envp, result);
		else
		{
			if (!ft_strncmp(*input, "\\\\", 2) || !ft_strncmp(*input, "\\$", 2) \
			|| !ft_strncmp(*input, "\\'", 2) || !ft_strncmp(*input, "\\\"", 2))
				(*input)++;
			result = add_char(result, **input);
			(*input)++;
		}
	}
	return (result);
}

char	*single_qoutation(char **input, char *arg)
{
	(*input)++;
	while (**input != 39)
	{
		arg = add_char(arg, **input);
		(*input)++;
	}
	(*input)++;
	return (arg);
}

char	*double_quotation(char **input, char **envp, char *arg)
{
	(*input)++;
	while (**input != 34)
	{
		if (**input == 36)
			arg = get_envp(input, envp, arg);
		else
		{
			if (!ft_strncmp(*input, "\\\\", 2) || !ft_strncmp(*input, "\\$", 2) \
			|| !ft_strncmp(*input, "\\\"", 2))
				(*input)++;
			arg = add_char(arg, **input);
			(*input)++;
		}
	}
	(*input)++;
	return (arg);
}

char	*get_envp(char **input, char **envp, char *arg)
{
	char	*key;
	char	*new;

	key = NULL;
	(*input)++;
	if (**input == '?')
	{
		(*input)++;
		free(arg);
		return (null_strjoin(arg, ft_itoa(g_error)));
	}
	while (ft_isalnum(**input) != 0)
	{
		key = add_char(key, **input);
		// if (key == NULL)
		// 	malloc error
		(*input)++;
	}
	if (key == NULL)
	{
		free(arg);
		return (null_strjoin(arg, "$"));
	}
	key = add_char(key, '=');
	new = null_strjoin(arg, get_var_value(envp, key));
	free(arg);
	free(key);
	// if (arg == NULL)
	// 	malloc error
	return (new);
}

char	*get_var_value(char **envp, char *key)
{
	char	*value;
	int		i;

	i = 0;
	while (envp[i] && (ft_strncmp(envp[i], key, ft_strlen(key)) != 0))
		i++;
	if (envp[i] != NULL)
		value = ft_strchr(envp[i], '=') + 1;
	else
	{
		value = ft_strdup("");
		if (value == NULL)
			return (NULL);
	}
	return (value);
}
