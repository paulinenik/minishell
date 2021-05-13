#include "mshell.h"


char	*parse_dollar(char **input, char **envp, char *arg)
{
	char	*key;
	char	*new;
	char	*status;

	key = NULL;
	(*input)++;
	if (**input == '?')
	{
		(*input)++;
		free(arg);
		status = ft_itoa(g_exit_status[1]);
		if (status == NULL)
			exit(ENOMEM);
		g_exit_status[0] = 0;
		new = null_strjoin(arg, status);
		free(status);
		return (new);
	}
	while (ft_isalnum(**input) != 0)
	{
		key = add_char(key, **input);
		if (key == NULL)
			exit(ENOMEM);
		(*input)++;
	}
	if (key == NULL)
	{
		if (**input == 34 || **input == 39)
			return (arg);
		free(arg);
		return (null_strjoin(arg, "$"));
	}
	key = add_char(key, '=');
	new = null_strjoin(arg, get_env_value(envp, key));
	free(arg);
	free(key);
	if (new == NULL)
		exit(ENOMEM);
	return (new);
}

char	*get_env_value(char **envp, char *key)
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
