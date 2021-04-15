#include "mshell.h"
#include <unistd.h>


void    get_pwd(t_all *all)
{
    char dir[66];
    if (!ft_strncmp(all->data->bin, "pwd\0", 4))
    {
        getcwd(dir, 66);
        printf("%s\n", dir);
    }
}

// void    get_env(t_data *data)
// {
//     if (!ft_strncmp(data->bin, "env", 3))

// }

char	**alph_sort(char **copy, int n)
{
		int j;
		int i;

		i = -1;
		while(++i < n)
		{
			// printf("%s\n", copy[i]);
			// printf("hellwo\n");
			j = i + 1;
        	while(j < n)
			{
				// printf("hellwo\n");
				if(ft_strcmp(copy[i], copy[j]) > 0)
				{
					char *tmp = copy[i];
					copy[i] = copy[j];
					copy[j] = tmp;
				}
				j++;
			}
		}
		return(copy);
}

int		save_index(t_data *data, char **envp)
{
	int i = -1;
	int j = -1;
	int k = 0;

	while(data->args[++i])
		{
			j = -1;
			while(envp[++j])
				if (!ft_strncmp(envp[j], data->args[i], ft_strlen(envp[j])))
				{
					k++;
					break ;
				}
		}
		return(k);
}

void    get_export(t_all *all)
{
	int i;
	int j;
	char **copy;
	int k = 0;
	int len;

	i = -1;
	j = -1;
	if (!ft_strncmp(all->data->bin, "export", 6) && (all->data->args == NULL))
	{
		copy = init(all->env, 0);
		while(copy[++i])
			copy = alph_sort(copy, i + 1);
		i = -1;
		while(copy[++i])
		 	printf("declare -x \"%s\"\n", copy[i]);
		while(--i >= 0)
		   free(copy[i]);
		free(copy);
		
			// while(all->env[++i])
			// 	printf("declare -x \"%s\"\n", all->env[i]);
	}
	else if (!ft_strncmp(all->data->bin, "export", 6) && all->data->args != NULL)
	{
		i = -1;
		while(all->data->args[++i]);
		while(all->env[++j]);
		len = j;
		k = save_index(all->data, all->env);
		copy = init(all->env, i - k);
		i = -1;
		while(all->data->args[++i])
		{
			j = -1;
			k = -1;
			while(all->env[++j])
			{
				if (!ft_strncmp(all->env[j], all->data->args[i], ft_strlen(all->env[j])))
				{
					k = i;
					break ;
				}
			}
			if (k == -1)
			{
				copy[len] = ft_strdup(all->data->args[i]);
				len++;
			}

		}
		copy[len] = NULL;
		
		j = -1;
		while(all->env[++j]);
		while(--j >= 0)
		   free(all->env[j]);
		free(all->env);
		all->env = copy;
		
	}
}

void    get_env(t_all *all)
{
	int i;

	i = -1;
	if (!ft_strncmp(all->data->bin, "env", 4))
		while(all->env[++i])
			printf("%s\n", all->env[i]);

}

void	get_cd(t_all *all)
{
	char dir[66];
	int i;
	char *key;

	i = 66;
	getcwd(dir, 66);
	if (!ft_strncmp(all->data->bin, "cd", 3))
	{
		if (all->data->args == NULL || all->data->args[0][0] == '~')
		{
			key = get_var_value(all->env,"HOME");
			if (key == NULL)
				printf("-%d-", chdir(all->home_path));
			else
				printf("-%d-", chdir(key));
		}
		else if ((!ft_strncmp(all->data->args[0], "..", 3)))
		{
			while (dir[--i] != '/')
				dir[i] = '\0';
			chdir(dir);
			//func(dir, "OLDPWD");
		}
		else if ((!ft_strncmp(all->data->args[0], "-", 2)))
		{
			key = get_var_value(all->env,"OLDPWD");
			if (key == NULL)
				printf("minishell: cd: OLDPWD not set\n");
			
			else 
				chdir(key);
		}
		else if ((!ft_strncmp(all->data->args[0], "/", 2)))
			chdir("/");
		else
		{
			if (chdir(all->data->args[0]) == -1)
				printf("minishell: cd: %s: No such file or directory\n", all->data->args[0]);

		}

	}
}

void	get_echo(t_all *all)
{
	int i;

	i = -1;
	if (!ft_strncmp(all->data->bin, "echo", 4))
	{
		if (all->data->args == NULL)
			printf("\n");
		else
		{
			while(all->data->args[++i])
			{
				write(1, all->data->args[i], ft_strlen(all->data->args[i]));
				write(1," ", 1);
			}
			write(1,"\n", 1);
		}
	}
	
}

