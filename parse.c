#include "mshell.h"

static void	to_process(t_all *all)
{
	if (data_size(all->data) > 1)
		revert_data(&all->data);
	get_pwd(all);
	// write(1, "inpwd process\n", 12);
	get_export(all);
	get_env(all);
	get_cd(all);
}

void	parse(char *input, t_all *all)
{
	if (ft_strlen(input) == 1)
		return;
	all->data = init_data();
	all->data->bin = init_exec_name(&input, all->env);
	// printf("|%s| %zu - input\n", input, ft_strlen(input));
	printf("%s - binary name\n", all->data->bin);
	while (*input != '\0')
	{
		if (*input == ' ')
		{
			all->data->args = get_args(&input, all->env);
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
	t_data *next_data;

	// printf("We are in specchar now!\n");
	if (**input == ';')
	{
		if (all->data->bin == NULL)
		{
			printf("syntax error\n");
			**input = '\0';
			return ;
		}
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
		if (all->data->bin == NULL || next_data->bin == NULL)
		{
			printf("syntax error\n");
			**input = '\0';
			return ;
		}
		add_data_front(&all->data, next_data);
	}
	//redirect
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
	while (**input == ' ')
		(*input)++;
	while (**input != '\0' && **input != ';' && **input != '|' && **input !='\n')
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
		return(NULL);
	list_size = ft_lstsize(list);
	array = (char **)malloc(sizeof(char *) * list_size + 1);
	if (array == NULL)
		exit(0);
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

	result = NULL;
	while (**input == ' ')
		(*input)++;
	while (**input != '\0' && **input !=' ' && **input != ';' && **input != '|' && **input !='\n')
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

	key = NULL;
	(*input)++;
	// printf("%s - input in get_envp\n", *input);
	while(**input != ' ' && **input != '\\' && **input != 39
	&& **input != 34 && **input != ';' && **input != '|' && **input != 36 && **input != '\0')
	{
		key = add_char(key, **input);
		if (key == NULL)
			return (NULL);
		(*input)++;
	}
	key = add_char(key, '=');
	if (arg == NULL)
		arg = ft_strdup(get_var_value(envp, key));
	else
		arg = ft_strjoin(arg, get_var_value(envp, key));
	free(key);
	if (arg == NULL)
		return (NULL);
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