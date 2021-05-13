#include "mshell.h"

static int	exec_builtin(t_all *all)
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

int	exec_cmd(t_all *all)
{
	char	**pwd;
	char	**argv;
	char	*path;
	int		status;
	pid_t	pid;
	DIR		*dir_stream;

	pwd = NULL;
	argv = NULL;
	if (all->data->bin[ft_strlen(all->data->bin) - 1] == '/')
	{
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
		return (1);
	}
	if (!ft_strchr(all->data->bin, '/'))
		path = check_path(all->data->bin, get_env_value(all->env, "PATH"));
	else
		path = ft_strdup(all->data->bin);
	if (path == NULL)
	{
		return_fd(all->data);
		printf("minishell: %s: command not found\n", all->data->bin);
		g_exit_status[0] = 127;
		return (1);
	}
	pid = fork();
	if (pid == 0)
	{
		if (all->data->args == NULL)
		{
			pwd = (char **)malloc(sizeof(char *) * 2);
			pwd[0] = ft_strdup(".");
			pwd[1] = NULL;
			status = execve(path, pwd, all->env);
		}
		else
		{
			argv = array_add_front(all->data->args, all->data->bin);
			status = execve(path, argv, all->env);
		}
		if (status == -1)
		{
			printf("minishell: %s: %s\n", path, strerror(errno));
			exit(127);
		}
	}
	wait(&status);
	g_exit_status[0] = status;
	free(path);
	td_array_clear(pwd);
	td_array_clear(argv);
	return (0);
}

char	*check_path(char *filename, char *path)
{
	char			**path_list;
	DIR				*dir_stream;
	struct dirent	*info;
	int				i;
	char			*newpath;

	i = 0;
	newpath = NULL;
	path_list = ft_split(path, ':');
	if (path_list == NULL)
	{
		free(filename);
		free(path);
		exit(ENOMEM);
	}
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
		if (info)
		{
			path_list[i] = add_char(path_list[i], '/');
			newpath = ft_strjoin(path_list[i], filename);
			closedir(dir_stream);
			break ;
		}
		closedir(dir_stream);
		i++;
	}
	td_array_clear(path_list);
	return (newpath);
}
