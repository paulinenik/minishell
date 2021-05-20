#include "mshell.h"
#include "libft.h"
#include <stdlib.h>
#include <dirent.h>
#include <stdio.h>

void	to_process(t_all *all)
{
	int		exit_status;
	t_data	*data;

	if (data_size(all->data) > 1)
		revert_data(&all->data);
	data = all->data;
	while (all->data != NULL)
	{
		change_fd(all->data);
		exit_status = exec_builtin(all);
		if (exit_status)
			exit_status = exec_cmd(all);
		return_fd(all->data);
		all->data = all->data->next;
	}
	all->data = data;
}

int	exec_builtin(t_all *all)
{
	if (!ft_strncmp(all->data->bin, "pwd", 4))
		g_exit_status[0] = get_pwd();
	else if (!ft_strncmp(all->data->bin, "export", 7))
		g_exit_status[0] = get_export(all);
	else if (!ft_strncmp(all->data->bin, "env", 4))
		g_exit_status[0] = get_env(all);
	else if (!ft_strncmp(all->data->bin, "cd", 3))
		g_exit_status[0] = get_cd(all);
	else if (!ft_strncmp(all->data->bin, "echo", 5))
		g_exit_status[0] = get_echo(all);
	else if (!ft_strncmp(all->data->bin, "unset", 6))
		g_exit_status[0] = get_unset(all);
	else if (!ft_strncmp(all->data->bin, "exit", 5))
		g_exit_status[0] = get_exit(all);
	else
		return (1);
	return (0);
}

int	exec_cmd(t_all *all)
{
	char	*path;

	if (all->data->bin[ft_strlen(all->data->bin) - 1] == '/')
	{
		check_for_directory(all);
		return (1);
	}
	path = get_path(all);
	if (path == NULL)
		return (1);
	if (all->data->args == NULL)
		init_cwd_argv(all);
	create_child_process(path, all);
	free(path);
	return (0);
}

void	check_for_directory(t_all *all)
{
	DIR		*dir_stream;

	return_fd(all->data);
	dir_stream = opendir(all->data->bin);
	if (dir_stream != NULL)
	{
		printf("minishell: %s: is a directory\n", all->data->bin);
		closedir(dir_stream);
	}
	else
		printf("minishell: %s: Not a directory\n", all->data->bin);
	g_exit_status[0] = 126;
}

char	*get_path(t_all *all)
{
	char	*path;

	if (ft_strchr(all->data->bin, '/') == NULL)
	{
		path = check_path(all->data->bin, get_env_value(all->env, "PATH"));
		if (path == NULL)
		{
			return_fd(all->data);
			printf("minishell: %s: command not found\n", all->data->bin);
			g_exit_status[0] = 127;
			return (NULL);
		}
	}
	else
		path = ft_strdup(all->data->bin);
	if (path == NULL)
		exit(ENOMEM);
	return (path);
}
