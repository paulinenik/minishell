#include "mshell.h"
#include "libft.h"
#include <stdlib.h>
#include <errno.h>

void	parse(char *input, t_all *all)
{
	g_exit_status[1] = g_exit_status[0];
	g_exit_status[0] = 0;
	all->operators_flag = 0;
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
		else if (ft_strchr("|&><;", *input) != NULL)
			check_specchar(&input, all);
		else
			input++;
	}
	if (all->data->bin && (g_exit_status[0] == 0 || data_size(all->data) > 1))
		to_process(all);
}

char	*init_exec_name(char **input, char **envp)
{
	char	*result;

	result = NULL;
	while (**input == ' ')
		(*input)++;
	while (**input != '\0' && \
	ft_strchr(" &><|;\n", **input) == NULL)
	{
		if (**input == 39)
			result = single_qoutation(input, result);
		else if (**input == 34)
			result = double_quotation(input, envp, result);
		else if (**input == 36)
			result = parse_dollar(input, envp, result);
		else
		{
			if (!ft_strncmp(*input, "\\", 1))
				(*input)++;
			result = add_char(result, **input);
			(*input)++;
		}
	}
	return (result);
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
	while (ft_strchr("|><&;\n", **input) == NULL && **input != '\0')
	{
		content = init_exec_name(input, envp);
		if (content != NULL)
		{
			item = ft_lstnew(content);
			if (item == NULL)
				exit(ENOMEM);
			ft_lstadd_back(&list, item);
			if (**input == ' ')
				(*input)++;
		}
	}
	args = list_to_array(list);
	return (args);
}

void	check_specchar(char **input, t_all *all)
{
	t_data	*next_data;

	if (**input == ';' || !ft_strncmp("&&", *input, 2))
		parse_semicolon(input, all);
	else if (**input == '|')
	{
		next_data = init_data();
		(*input)++;
		if (**input != '|')
			next_data->bin = init_exec_name(input, all->env);
		next_data->fd[0] = parse_pipes(input, all);
		if (next_data->fd[0] == -1)
		{	
			clear_data(&next_data);
			return ;
		}
		add_data_front(&all->data, next_data);
		if (all->data->bin == NULL)
			g_exit_status[0] = 258;
	}
	else
		redirect_parse(input, all);
}
