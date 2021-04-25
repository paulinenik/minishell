#include "mshell.h"
#include <unistd.h>


int    get_pwd(t_all *all)
{
    char dir[1024];
    if (ft_strncmp(all->data->bin, "pwd\0", 4))
		return (1);
	getcwd(dir, 1024);
	printf("%s\n", dir);
	return (0);
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


int		check_for_value(t_all *all, int i)
{
	int j;

	j = -1;
	while(all->data->args[i][++j])
		if(all->data->args[i][j] == '=')
			return (j);
	return(-1);
}

int    get_export(t_all *all)
{
	int i;
	int j;
	char **copy;
	int k = 0;
	int len;
	char *str;

	i = -1;
	j = -1;
	if (ft_strncmp(all->data->bin, "export\0", 7))
		return(1);
	if (all->data->args == NULL)
		print_export(all, -1, -1, copy);
	else if (all->data->args != NULL)
	{
		check_export(all, -1, len, copy);
		// i = -1;
		// int nbr = 0;
		// while(all->data->args[++i]);
		// while(all->env[++j]);
		// len = j;
		// k = save_index(all->data, all->env);
		// copy = init(all->env, i - k);
		// i = -1;
		// while(all->data->args[++i])
		// {
		// 	j = -1;
		// 	k = -1;
		// 	int temp = -1;
		// 	nbr = check_for_value(all, i);
		// 	while(all->env[++j])
		// 	{
		// 		temp = -1;
		// 		while(all->data->args[i][++temp])
		// 			{
		// 				if(all->data->args[i][temp] == '=')
		// 					break ;
		// 				if(ft_isalnum(all->data->args[i][temp]) == 0)
		// 				{
		// 					// write(1,&all->data->args[i][temp], 1);
		// 					temp = -2;
		// 					break ;
		// 				}
		// 			}
		// 		if ((all->data->args[i][0] <= '9' && all->data->args[i][0] >= '0') || temp == -2)
		// 		{
		// 				write(1, "minishell: export: ", 20);
		// 				write(1,all->data->args[i], ft_strlen(all->data->args[i]));
		// 				write(1,": not a valid identifier\n",26);
		// 				// printf("minishell: export: %s: not a valid identifier", all->data->args[i]);
		// 				g_error = 1;
		// 			k = i;
		// 			break ;
		// 		}
		// 		if (nbr != -1)
		// 		{
		// 			if(!ft_strncmp(all->data->args[i], all->env[j], nbr))
		// 			{
		// 				free(copy[j]);
		// 				copy[j] = NULL;
		// 				copy[j] = ft_strdup(all->data->args[i]);
		// 				k = 0;
		// 				break ;
		// 			}
		// 		}
		// 	}
		// 	if (k == -1 && nbr != -1)
		// 	{
		// 		copy[len] = ft_strdup(all->data->args[i]);
		// 		len++;
		// 	}
		// }
		// copy[len] = NULL;
		// check_export(all, -1, len, copy);
		// j = -1;
		// while(all->env[++j]);
		// while(--j >= 0)
		//    free(all->env[j]);
		// free(all->env);
		// all->env = copy;
	}
	return (0);
}

int    get_env(t_all *all)
{
	int i;

	i = -1;
	if (ft_strncmp(all->data->bin, "env", 4))
		return (1);
	while(all->env[++i])
		printf("%s\n", all->env[i]);
	return (0);
}

void	check_dir(char *str)
{
	if (chdir(str) == -1)
		printf("minishell: cd: %s: No such file or directory\n", str);
}

int	get_cd(t_all *all)
{
	char dir[1024];
	int i;
	char *key;

	key = NULL;
	i = 1024;
	getcwd(dir, 1024);
	if (ft_strncmp(all->data->bin, "cd", 3))
		return (1);
	if (all->data->args == NULL || all->data->args[0][0] == '~')
	{	
		if (all->data->args == NULL)
		{
			printf("minishell: cd: HOME not set\n");
			return (0);
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
	return (0);
}

int    get_unset(t_all *all)
{
	int i;
	int j;
	char **copy;
	int k = 0;
	int f = 0;
	i = -1;
	j = -1;
	if (ft_strncmp(all->data->bin, "unset", 6))
		return (1);
	if ((all->data->args != NULL))
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
	return (0);
}

int	get_echo(t_all *all)
{
	int i;

	i = -1;
	if (ft_strncmp(all->data->bin, "echo", 5))
		return (1);
	if (all->data->args == NULL)
		write(1,"brya\n", 5);
	else
	{
		while(all->data->args[++i])
		{
			//write(1, all->data->args[i], ft_strlen(all->data->args[i]));
			if (!ft_strncmp(all->data->args[i], "$?", 2))
				write(1,"brya\n", 5);
				//printf("%ddnfidifd", g_error);
			else
			{
				write(1, all->data->args[i], ft_strlen(all->data->args[i]));
				write(1,"dfd ", 1);
			}
		}
		write(1,"\n", 1);
	}
	return (0)	;
}

// int	get_echo(t_all *all)
// {
// 	int i;

// 	i = -1;
// 	if (ft_strncmp(all->data->bin, "echo", 5))
// 		return(1);
// 		if (all->data->args == NULL)
// 			printf("\n");
// 		else
// 		{
// 			while(all->data->args[++i])
// 			{
// 				if (ft_strcmp(all->data->args[i], "$?"))
// 					ft_putnbr_fd(g_error, 1);
// 				else
// 				{
// 					write(1, all->data->args[i], ft_strlen(all->data->args[i]));
// 					write(1," ", 1);
// 				}
// 			}
// 			write(1,"\n", 1);
// 		}
// 	return (0);
// }
	

