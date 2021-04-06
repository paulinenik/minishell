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
	data->arg->bin = NULL;
	//malloc for args
	return (data);
}

void	parse(char *input, char **envp)
{
	t_data	*data;

	data = init_data();
	init_exec_name(&input, envp, data->arg);
	while (input)
	{
		// init_arg(&input, envp, data->arg);
		// check_specchar(&input, envp, data);
	}
	free(input);
	//pass to process(data, envp)
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

void	init_exec_name(char **input, char **envp, t_args *arg)
{
	char	*exec;
	size_t	name_len;

	exec = NULL;
	while (*input != NULL && **input !=' ' && **input != ';' && **input != '|')
	{
		if (**input == 39)
			exec = single_qoutation(input, exec);
		else if (**input == 34)
			exec = double_quotation(input, envp, exec);
		else if (**input == 36)
			exec = get_envp(input, envp, exec);
		// if (**input == '\')
			//экранирование
		else
			exec = add_char(exec, **input);
		(*input)++;
	}
	if (arg->bin == NULL)
		arg->bin = exec;
	// else:
	// add args to list
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
			arg = get_envp_val(input, envp, arg);
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
	while(**input != ' ' && **input != '\\' && **input != 39
	&& **input != 34 && **input != ';' && **input != '|' && **input != 36)
	{
		key = add_char(key, **input);
		if (key == NULL)
			return (NULL);
		(*input)++;
	}
	arg = ft_strjoin(arg, get_var_value(envp, key)); //free key
	if (arg == NULL)
		return (NULL);
	return (arg);
}

char *get_var_value(char **envp, char *key)
{
	char	*value;
	int		i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], key, ft_strlen(key)) != 0)
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

int main(int argc, char **argv, char **envp)
{
	char *s;

	(void)argc;
	(void)argv;
	s = NULL;
	// s = ft_strdup("");
	// s = ft_strdup("Hello World");
	// s = add_char(s, '!');
	printf("%s\n", envp[0]);
	free(s);
}