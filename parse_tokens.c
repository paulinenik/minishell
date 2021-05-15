#include "mshell.h"

void	parse_semicolon(char **input, t_all *all)
{
	if (all->data->bin == NULL)
	{
		if (*(*input + 1) == ';')
			printf("minishell: syntax error near unexpected token `;;'\n");
		else
			printf("minishell: syntax error near unexpected token `;'\n");
		**input = '\0';
		g_exit_status[0] = 258;
		return ;
	}
	to_process(all);
	clear_all(&all->data);
	all->data = init_data();
	(*input)++;
	all->data->bin = init_exec_name(input, all->env);
}

int	parse_pipes(char **input, t_all *all)
{
	int		pipes_fd[2];

	if (all->data->bin == NULL)
	{
		if (*(*input + 1) == '|')
			printf("minishell: syntax error near unexpected token `||'\n");
		else
			printf("minishell: syntax error near unexpected token `|'\n");
		**input = '\0';
		g_exit_status[0] = 258;
		return (0);
	}
	if (pipe(pipes_fd) < 0)
	{
		printf("minishell: %s\n", strerror(errno));
		**input = '\0';
		g_exit_status[0] = errno;
		return (0);
	}
	if (all->data->fd[1] == 1)
		all->data->fd[1] = pipes_fd[1];
	return (pipes_fd[0]);
}

void	redirect_parse(char **input, t_all *all)
{
	if (**input == '>' && *(*input + 1) == '<')
	{
		printf("minishell: syntax error near unexpected token `<'\n");
		**input = '\0';
		g_exit_status[0] = 258;
	}
	if (**input == '>' && *(*input + 1) == '>')
	{
		(*input)++;
		redirect_append(input, all);
	}
	if (**input == '>')
		redirect_write(input, all);
	if (**input == '<')
	{
		if (*(*input + 1) == '>')
			(*input)++;
		redirect_read(input, all);
	}
}
