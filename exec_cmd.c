#include "mshell.h"


static int	exec_builtin(t_all * all)
{
	if (!get_pwd(all))
		return (0);
	if (!get_export(all))
		return (0);
	if (!get_env(all))
		return (0);
	if (!get_cd(all))
		return (0);
	if (!get_echo(all))
		return (0);
	if (!get_unset(all))
		return (0);
	return (1);
}

void	to_process(t_all *all)
{
	int exit_status;

	exit_status = 1;
	change_fd(all->data);
	if (data_size(all->data) > 1)
		revert_data(&all->data);
	exit_status = exec_builtin(all);
	if (exit_status == 1)
		exit_status = exec_cmd(all);
	return_fd(all->data);
}

int exec_cmd(t_all * all)
{
	char **pwd;
	char *path;

	pwd = NULL;
	if (!ft_strchr(all->data->bin, '/'))
		path = check_path(all->data->bin, getenv("PATH"));
	else
		path = ft_strdup(all->data->bin);
	if (all->data->args == NULL)
	{
		// write(1, "hello\n", 6);
		pwd = (char **)malloc(sizeof(char) * 2);
		pwd[0] = ft_strdup(".");
		pwd[1] = NULL;
		execve(path, pwd, all->env);
	}
	else
		execve(path, all->data->args, all->env);
	free(path);
	td_array_clear(pwd);
	return (0);
}

char *check_path(char *filename, char *path)
{
	char			**path_list;
	DIR 			*dir_stream;
	struct dirent	*info;
	int				i;
	char 			*newpath;

	i = 0;
	path_list = ft_split(path, ':');
	newpath = NULL;
	// if (path_list == NULL)
	// 	malloc_error
	while(path_list[i] != NULL)
	{
		dir_stream = opendir(path_list[i]);
		// if (dir_stream == NULL)
		// 	error
		info = readdir(dir_stream);
		while (info != NULL && ft_strcmp(info->d_name, filename))
			info = readdir(dir_stream);
		if (info)
		{
			newpath = add_char(path_list[i], '/');
			newpath = ft_strjoin(newpath, filename);
		}
		closedir(dir_stream);
		i++;
	}
	// td_array_clear(path_list);
	return (newpath);
}