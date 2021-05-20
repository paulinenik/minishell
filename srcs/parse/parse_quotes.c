#include "mshell.h"
#include "libft.h"
#include <stdlib.h>

char	*single_qoutation(char **input, char *arg)
{
	(*input)++;
	while (**input != 39 && **input !='\0')
	{
		arg = add_char(arg, **input);
		(*input)++;
	}
	if (**input !='\0')
		(*input)++;
	if (arg == NULL)
		return (ft_strdup(""));
	return (arg);
}

char	*double_quotation(char **input, char **envp, char *arg)
{
	(*input)++;
	while (**input != 34 && **input !='\0')
	{
		if (**input == 36)
			arg = parse_dollar(input, envp, arg);
		else
		{
			if (!ft_strncmp(*input, "\\\\", 2) || !ft_strncmp(*input, "\\$", 2) \
			|| !ft_strncmp(*input, "\\\"", 2))
				(*input)++;
			arg = add_char(arg, **input);
			(*input)++;
		}
	}
	if (**input !='\0')
		(*input)++;
	if (arg == NULL)
		return (ft_strdup(""));
	return (arg);
}
