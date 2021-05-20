#include "mshell.h"
#include "libft.h"
#include <stdlib.h>
#include <errno.h>

char	*parse_dollar(char **input, char **envp, char *arg)
{
	char	*key;
	char	*new;

	(*input)++;
	if (**input == '?')
		return (get_exit_status(input, arg));
	key = get_env_key(input);
	if (key == NULL)
	{
		if (**input == 34 || **input == 39)
			return (arg);
		free(arg);
		return (null_strjoin(arg, "$"));
	}
	new = null_strjoin(arg, get_env_value(envp, key));
	if (new == NULL)
		exit(ENOMEM);
	free(arg);
	free(key);
	return (new);
}

char	*get_env_key(char **input)
{
	char	*key;

	key = NULL;
	while (ft_isalnum(**input) != 0)
	{
		key = add_char(key, **input);
		if (key == NULL)
			exit(ENOMEM);
		(*input)++;
	}
	if (key != NULL)
		key = add_char(key, '=');
	return (key);
}

char	*get_exit_status(char **input, char *arg)
{
	char	*status;
	char	*new;

	(*input)++;
	status = ft_itoa(g_exit_status[1]);
	if (status == NULL)
		exit(ENOMEM);
	g_exit_status[0] = 0;
	new = null_strjoin(arg, status);
	free(arg);
	free(status);
	return (new);
}

char	*get_env_value(char **envp, char *key)
{
	char	*value;
	int		i;

	i = 0;
	if (key == NULL)
		return (NULL);
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
