#include "mshell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>

void	create_child_process(char *path, t_all *all)
{
	pid_t	pid;
	int		status;
	char	**argv;

	argv = NULL;
	pid = fork();
	if (pid == -1)
	{
		g_exit_status[0] = errno;
		printf("minishell: %s: %s\n", path, strerror(errno));
		return ;
	}
	if (pid == 0)
	{	
		argv = array_add_front(all->data->args, all->data->bin);
		status = execve(path, argv, all->env);
		if (status == -1)
		{
			printf("minishell: %s: %s\n", path, strerror(errno));
			exit(127);
		}
	}
	wait(&g_exit_status[0]);
	g_exit_status[0] = g_exit_status[0] >> 8;
	td_array_clear(argv);
}

void	init_cwd_argv(t_all *all)
{
	all->data->args = (char **)malloc(sizeof(char *) * 2);
	if (all->data->args == NULL)
		exit(ENOMEM);
	all->data->args[0] = ft_strdup(".");
	if (all->data->args[0] == NULL)
		exit(ENOMEM);
	all->data->args[1] = NULL;
}

char	*check_path(char *filename, char *path)
{
	char	*directory;
	char	*full_path;
	char	**path_list;

	full_path = NULL;
	path_list = ft_split(path, ':');
	if (path_list == NULL)
		exit(ENOMEM);
	directory = search_bin(filename, path_list);
	if (directory != NULL)
	{
		directory = add_char(directory, '/');
		full_path = ft_strjoin(directory, filename);
	}
	free(directory);
	td_array_clear(path_list);
	return (full_path);
}

char	*search_bin(char *filename, char **path_list)
{
	DIR				*dir_stream;
	struct dirent	*info;
	int				i;

	i = 0;
	while (path_list[i] != NULL)
	{
		dir_stream = opendir(path_list[i]);
		if (dir_stream == NULL)
		{
			printf("minishell: %s: %s\n", path_list[i], strerror(errno));
			exit(errno);
		}
		info = readdir(dir_stream);
		while (info != NULL && ft_strcmp(info->d_name, filename))
			info = readdir(dir_stream);
		closedir(dir_stream);
		if (info != NULL)
			break ;
		i++;
	}
	return (ft_strdup(path_list[i]));
}
