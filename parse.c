#include "mshell.h"

t_data	*init_data(void)
{
	t_data *data;

	data = (t_data *)malloc(sizeof(t_data));
	// if (data == NULL)
	// 	error
	data->arg = (t_args *)malloc(sizeof(t_args));
	// if (data->arg == NULL)
	// error
	data->next = NULL;
	return (data);
}

void	parse(char *input, char **envp)
{
	t_data	*data;

	data = init_data();
	init_exec_name(&input, envp, data->arg);
	while (input)
	{
		init_arg(&input, envp, data->arg);
		check_specchar(&input, envp, data);
	}
	free(input);
	//pass to process(data, envp)
}

void	ft_realloc(void *data)
{
	char *reallocated;

	ft_git	
}

void	init_exec_name(char **input, char **envp, t_args *arg)
{
	char	*exec;
	size_t	name_len;

	// exec = (char *)malloc(sizeof(char));
	// if (exec == NULL)
	//error
	while (*input != NULL && **input !=' ' && **input != ';' && **input != '|')
	{
		if (**input == 39)
			exec = single_qoutation(input, exec);
		if (**input == 34)
			exec = double_quotation(input, envp, exec);
		if (**input == 36)
			exec = get_envp_val(input, envp, exec);
		// if (**input == '\')
			//экранирование
		exec = ft_strjoin(exec, )
		(*input)++;
		
	}
}