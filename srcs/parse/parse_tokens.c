#include "mshell.h"

void	parse_semicolon(char **input, t_all *all)
{
	if (**input == '&')
		(*input)++;
	if (all->data->bin == NULL)
	{
		if (*(*input + 1) == ';')
			printf("minishell: syntax error near unexpected token `;;'\n");
		else
			printf("minishell: syntax error near unexpected token `;'\n");
		stop_parse(input, 258);
		return ;
	}
	if ((all->operators_flag == '|' && g_exit_status[1] != 0) || \
		(all->operators_flag == '&' && g_exit_status[1] == 0) || \
		all->operators_flag == 0)
		to_process(all);
	if (**input != ';')
		toggle_operator_flag(input, all);
	clear_data(&all->data);
	all->data = init_data();
	(*input)++;
	all->data->bin = init_exec_name(input, all->env);
}

void	toggle_operator_flag(char **input, t_all *all)
{
	all->operators_flag = (int)**input;
	if ((**input == '|' && g_exit_status[0] == 0) || \
		(**input == '&' && g_exit_status[0] != 0))
		*(*input + 1) = '\0';
	else
	{
		g_exit_status[1] = g_exit_status[0];
		g_exit_status[0] = 0;
	}
}

int	parse_pipes(char **input, t_all *all)
{
	int		pipes_fd[2];

	if (all->data->bin == NULL)
	{
		if (**input == '|')
			printf("minishell: syntax error near unexpected token `||'\n");
		else
			printf("minishell: syntax error near unexpected token `|'\n");
		stop_parse(input, 258);
		return (-1);
	}
	if (!ft_strncmp(*input, "|", 1))
	{	
		parse_semicolon(input, all);
		return (-1);
	}
	if (pipe(pipes_fd) < 0)
	{
		printf("minishell: %s\n", strerror(errno));
		stop_parse(input, errno);
		return (-1);
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
		stop_parse(input, 258);
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
