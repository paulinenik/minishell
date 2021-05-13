#include "mshell.h"

int	*init_fd(void)
{
	int	*fds;

	fds = (int *)malloc(sizeof(int) * 2);
	fds[0] = 0;
	fds[1] = 1;
	return (fds);
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
	// if (**input == '<' && *(input + 1) == '<')
	// {
	// 	(*input)++;
	// 	// wait until
	// }
	if (**input == '>')
		redirect_write(input, all);
	if (**input == '<')
	{
		if (*(*input + 1) == '>')
			(*input)++;
		redirect_read(input, all);
	}
}

void	redirect_append(char **input, t_all *all)
{
	char	*path;

	(*input)++;
	path = init_exec_name(input, all->env);
	if (path == NULL)
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		**input = '\0';
		g_exit_status[0] = 258;
		return ;
	}	
	if (all->data->fd[1] != 1)
		close(all->data->fd[1]);
	all->data->fd[1] = open(path, O_APPEND | O_CREAT | O_WRONLY, 0644);
	if (all->data->fd[1] == -1)
	{
		printf("minishell: %s: %s\n", path, strerror(errno));
		**input = '\0';
		g_exit_status[0] = 1;
		return ;
	}
	free(path);
}

void	redirect_write(char **input, t_all *all)
{
	char	*path;

	(*input)++;
	path = init_exec_name(input, all->env);
	if (path == NULL)
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		**input = '\0';
		g_exit_status[0] = 258;
		return ;
	}
	if (all->data->fd[1] != 1)
		close(all->data->fd[1]);
	all->data->fd[1] = open(path, O_TRUNC | O_CREAT | O_WRONLY, 0644);
	if (all->data->fd[1] == -1)
	{
		printf("minishell: %s: %s\n", path, strerror(errno));
		**input = '\0';
		g_exit_status[0] = 1;
		return ;
	}
	free(path);
}

void	redirect_read(char **input, t_all *all)
{
	char	*path;
	(*input)++;
	path = init_exec_name(input, all->env);
	if (path == NULL)
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		**input = '\0';
		g_exit_status[0] = 258;
		return ;
	}
	if (all->data->fd[0] != 0)
		close(all->data->fd[0]);
	all->data->fd[0] = open(path, O_RDONLY, 0644);
	if (all->data->fd[0] == -1)
	{
		printf("minishell: %s: %s\n", path, strerror(errno));
		**input = '\0';
		g_exit_status[0] = 1;
		return ;
	}
	free(path);
}

void	change_fd(t_data *data)
{
	if (data->fd[0] != 0)
	{
		data->old_fd[0] = dup(0);
		dup2(data->fd[0], 0);
		close(data->fd[0]);
	}
	if (data->fd[1] != 1)
	{
		data->old_fd[1] = dup(1);
		dup2(data->fd[1], 1);
		close(data->fd[1]);
	}
}

void	return_fd(t_data *data)
{
	if (data->fd[0] != 0)
	{
		dup2(data->old_fd[0], 0);
		close(data->old_fd[0]);
	}
	if (data->fd[1] != 1)
	{
		dup2(data->old_fd[1], 1);
		close(data->old_fd[1]);
	}
}
