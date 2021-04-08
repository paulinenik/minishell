#include "mshell.h"

t_data	*init_data(void)
{
	t_data *data;

	data = (t_data *)malloc(sizeof(t_data));
	// if (data == NULL)
	// 	error
	data->bin = NULL;
	//malloc for args
	data->next = NULL;
	return (data);
}

void	parse(char *input, char **envp)
{
	t_data	*data;

	data = init_data();
	// printf("%s - input\n", input);
	data->bin = init_exec_name(&input, envp);
	printf("%s - binary name\n", data->bin);
	while (*input != '\0')
	{
		if (*input == ' ')
		{
			data->args = get_args(&input, envp);
		}
		// check_specchar(&input, envp, data);
		input++;
	}
	// pass to process(data, envp)
	get_pwd(data);
	// exit(0);
}

char	**get_args(char **input, char **envp)
{
	char	**args;
	char	*content;
	t_list	*item;
	t_list	*list;

	args = NULL;
	content = NULL;
	(*input)++;
	while (**input != '\0' && **input != ';' && **input != '|' && **input !='\n')
	{
		content = init_exec_name(input, envp);
		item = ft_lstnew(content);
		if (item == NULL)
			exit(0);
		printf("%s - output\n", *input);
		ft_lstadd_back(&list, item);
		// free(content);
		// free(item);
		// content = NULL;
		if (**input == ' ')
			(*input)++;
		// printf("%s - output\n", *input);
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
	array = (char **)malloc(sizeof(char *) * ft_lstsize(list) + 1);
	if (array == NULL)
		exit(0);
	list_size = ft_lstsize(list);
	printf("%d - size of list\n", list_size);
	while (i < list_size)
	{
		array[i] = ft_strdup(list->content);
		i++;
		list = list->next;
	}
	array[i] = NULL;
	while(i >= 0)
	{
		printf("%s - arg[%d]\n", array[i], i);
		i--;
	}
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
		return(NULL);
	ft_memcpy(reallocated, str, str_len);
	reallocated[str_len] = c;
	reallocated[str_len + 1] = '\0';
	free(str);
	return(reallocated);
}

char	*init_exec_name(char **input, char **envp)
{
	char	*result;
	// size_t	name_len;

	result = NULL;
	// printf("|%s |- input\n", *input);
	while (**input != '\0' && **input !=' ' && **input != ';' && **input != '|' && **input !='\n')
	{
		if (**input == 39)
			result = single_qoutation(input, result);
		else if (**input == 34)
			result = double_quotation(input, envp, result);
		else if (**input == 36)
			result = get_envp(input, envp, result);
		// if (**input == '\')
			//экранирование
		else
		{
			result = add_char(result, **input);
			(*input)++;
		}
		// printf("|%s| - input in exec-name\n", *input);
	}
	return (result);
}

char	*single_qoutation(char **input, char *arg)
{
	(*input)++;
	while (**input != 39 && **input != '\n')
	{
		arg = add_char(arg, **input);
		(*input)++;
	}
	// (*input)++;
	return (arg);
}

char	*double_quotation(char **input, char **envp, char *arg)
{
	(*input)++;
	while (**input != 34)
	{
		if (**input == 36)
			arg = get_envp(input, envp, arg);
		// if (**input == '\')
			//экранирование
		arg = add_char(arg, **input);
		(*input)++;
	}
	(*input)++;
	return (arg);
}

char	*get_envp(char **input, char **envp, char *arg)
{
	char	*key;

	key = NULL;
	(*input)++;
	// printf("%s - input in get_envp\n", *input);
	while(**input != ' ' && **input != '\\' && **input != 39
	&& **input != 34 && **input != ';' && **input != '|' && **input != 36 && **input != '\n')
	{
		key = add_char(key, **input);
		if (key == NULL)
			return (NULL);
		(*input)++;
	}
	key = add_char(key, '=');
	// printf("%s - key in get_envp\n", key);
	if (arg == NULL)
		arg = ft_strdup(get_var_value(envp, key));
	else
		arg = ft_strjoin(arg, get_var_value(envp, key)); //free key
	if (arg == NULL)
		return (NULL);
	// printf("%s - arg in get_envp\n", arg);
	return (arg);
}

char *get_var_value(char **envp, char *key)
{
	char	*value;
	int		i;

	i = 0;
	// printf("%s - key\n", key);
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
	// printf("%s - value\n", value);
	return (value);
}