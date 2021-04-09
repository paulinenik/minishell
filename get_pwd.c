#include "mshell.h"
#include <unistd.h>

void    get_pwd(t_data *data)
{
	char dir[66];
	if (!ft_strncmp(data->bin, "pwd", 3))
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
		int l;
		for(int i = 0 ; i < n; i++)
		{
			printf("%s\n", copy[i]);
			printf("hellwo\n");
        	for(int j = i + 1; j < n; j++)
			{
				printf("hellwo\n");
				if(ft_strcmp(copy[i], copy[j]) > 0)
				{
					char *tmp = copy[i];
					copy[i] = copy[j];
					copy[j] = tmp;
				}
    
			}
		}
		return(copy);
}

int		save_index(t_data *data)
{
	int i = -1;
	int j = -1;
	int k = 0;

	while(data->args[++i])
		{
			j = -1;
			while(data->new[++j])
				if (!ft_strncmp(data->new[j], data->args[i], ft_strlen(data->new[j])))
				{
					k++;
					break ;
				}
		}
		return(k);
}

void    get_export(t_data *data)
{
	int i;
	int j;
	int nbr;
	char **copy;
	int k = 0;
	int len;

	i = -1;
	j = -1;
	if (!ft_strncmp(data->bin, "export", 6) && (data->args == NULL))
			while(data->new[++i])
				printf("declare -x \"%s\"\n", data->new[i]);
	else if (!ft_strncmp(data->bin, "export", 6) && data->args != NULL)
	{
		i = -1;
		while(data->args[++i]);
		nbr = i;
		while(data->new[++j]);
		len = j;
		k = save_index(data);
		copy = init(data->new, i - k);
		i = -1;
		while(data->args[++i])
		{
			j = -1;
			k = -1;
			while(data->new[++j])
			{
				if (!ft_strncmp(data->new[j], data->args[i], ft_strlen(data->new[j])))
				{
					k = i;
					break ;
				}
			}
			if (k == -1)
			{
				copy[len] = ft_strdup(data->args[i]);
				len++;
			}

		}
		copy[len] = NULL;
		i = -1;
		while(copy[++i]);
		copy = alph_sort(copy, i);
		j = -1;
		while(data->new[++j]);
		while(--j >= 0)
		   free(data->new[j]);
		free(data->new);
		data->new = copy;
		i = -1;
		while(copy[++i])
			printf("declare -x \"%s\"\n", copy[i]);
	}
}