#include "mshell.h"

void	parse(char *input, t_all *all)
{
	g_error = 0;
	if (ft_strlen(input) == 0)
		return ;
	all->data = init_data();
	all->data->bin = init_exec_name(&input, all->env);
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
	if (all->data->bin && g_error == 0)
		to_process(all);
}

void	check_specchar(char **input, t_all *all)
{
	t_data	*next_data;
	int		pipes_fd[2];

	if (**input == ';')
	{
		if (all->data->bin == NULL)
		{
			if (*(*input + 1) == ';')
				printf("minishell: syntax error near unexpected token `;;'\n");
			else
				printf("minishell: syntax error near unexpected token `;'\n");
			**input = '\0';
			g_error = 258;
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
		if (all->data->bin == NULL || next_data->bin == NULL)
		{
			if (*(*input + 1) == '|')
				printf("minishell: syntax error near unexpected token `||'\n");
			else
				printf("minishell: syntax error near unexpected token `|'\n");
			**input = '\0';
			g_error = 258;
			return ;
		}
		if (pipe(pipes_fd) < 0)
			printf("error\n");
		if (all->data->fd[1] == 1)
			all->data->fd[1] = pipes_fd[1];
		next_data = init_data();
		(*input)++;
		next_data->bin = init_exec_name(input, all->env);
		next_data->fd[0] = pipes_fd[0];
		add_data_front(&all->data, next_data);
		if (all->data->bin == NULL)
			g_error = 258;
	}
	else
		redirect_parse(input, all);
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
	while (**input != '\0' && **input != ';' && **input != '|' && **input != '\n' && **input != '>' && **input != '<')
	{
		content = init_exec_name(input, envp);
		if (content != NULL)
		{
			item = ft_lstnew(content);
			// if (item == NULL)
			// 	exit(0);
			ft_lstadd_back(&list, item);
			if (**input == ' ')
				(*input)++;
		}
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
	// 	printf("|%s| - arg[%d]\n", array[i], i);
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
		if (**input != 34 || **input != 39)
			return(arg);
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
