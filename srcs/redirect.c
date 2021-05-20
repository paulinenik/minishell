#include "mshell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

void	redirect_append(char **input, t_all *all)
{
	char	*path;

	(*input)++;
	path = init_exec_name(input, all->env);
	if (path == NULL)
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		stop_parse(input, 258);
		return ;
	}	
	if (all->data->fd[1] != 1)
		close(all->data->fd[1]);
	all->data->fd[1] = open(path, O_APPEND | O_CREAT | O_WRONLY, 0644);
	if (all->data->fd[1] == -1)
	{
		printf("minishell: %s: %s\n", path, strerror(errno));
		stop_parse(input, 1);
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
		stop_parse(input, 258);
		return ;
	}
	if (all->data->fd[1] != 1)
		close(all->data->fd[1]);
	all->data->fd[1] = open(path, O_TRUNC | O_CREAT | O_WRONLY, 0644);
	if (all->data->fd[1] == -1)
	{
		printf("minishell: %s: %s\n", path, strerror(errno));
		stop_parse(input, 1);
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
		stop_parse(input, 258);
		return ;
	}
	if (all->data->fd[0] != 0)
		close(all->data->fd[0]);
	all->data->fd[0] = open(path, O_RDONLY, 0644);
	if (all->data->fd[0] == -1)
	{
		printf("minishell: %s: %s\n", path, strerror(errno));
		stop_parse(input, 1);
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
