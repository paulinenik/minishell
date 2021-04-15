#include "mshell.h"
#include <unistd.h>


void    get_pwd(t_all *all)
{
    char dir[1024];
    if (!ft_strncmp(all->data->bin, "pwd\0", 4))
    {
        getcwd(dir, 1024);
        printf("%s\n", dir);
    }
}

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
				if (!ft_strcmp(envp[j], data->args[i]))
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
				if (!ft_strcmp(all->env[j], all->data->args[i]))
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

void	check_dir(char *str)
{
	if (chdir(str) == -1)
		printf("minishell: cd: %s: No such file or directory\n", str);
}

void	get_cd(t_all *all)
{
	char dir[1024];
	int i;
	char *key;

	key = NULL;
	i = 1024;
	getcwd(dir, 1024);
	if (!ft_strncmp(all->data->bin, "cd", 3))
	{
		if (all->data->args == NULL || all->data->args[0][0] == '~')
		{	
			if (all->data->args == NULL)
			{
				printf("minishell: cd: HOME not set\n");
				return ;
			}
			key = get_var_value(all->env,"HOME");
			if (key == NULL || key[0] == 0)
				chdir(all->home_path);
			else
				check_dir(key);
		}
		// else if ((!ft_strncmp(all->data->args[0], "-", 2)))
		// {
		// 	key = get_var_value(all->env,"OLDPWD");
		// 	if (key == NULL || key[0] == 0)
		// 		printf("minishell: cd: OLDPWD not set\n");
		// 	else
		// 		check_dir(key);
		// }
		else
			check_dir(all->data->args[0]);
	}
}

void    get_unset(t_all *all)
{
	int i;
	int j;
	char **copy;
	int k = 0;
	int f = 0;
	i = -1;
	j = -1;
	if (!ft_strncmp(all->data->bin, "unset", 5) && (all->data->args != NULL))
	{
		while(all->data->args[++i])
		{
			j = -1;
			while(all->env[++j])
				if (!ft_strncmp(all->env[j], all->data->args[i], ft_strlen(all->data->args[i])))
				{
					k++;
					break ;
				}
		}
		i = -1;
		j = -1;
		while(all->env[++i]);
		copy = malloc((i + 1 - k) * sizeof(char *));
		copy[i - k] = NULL;
		i = -1;
		while(all->env[++i])
			{
				j = -1;
				k = -1;
				while(all->data->args[++j])
				{
					k = (ft_strncmp(all->env[i], all->data->args[j], ft_strlen(all->data->args[j])));
					if (k == 0)
						break ;
				}
				if (k != 0)
				{
					copy[f] = ft_strdup(all->env[i]);
					f++;
				}
			}
			copy[f] = NULL;

		j = -1;
		while(all->env[++j]);
		while(--j >= 0)
		   free(all->env[j]);
		free(all->env);
		all->env = copy;
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

