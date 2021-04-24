#include "mshell.h"

void print_export(t_all *all, int i, int j, char **copy)
{
    copy = init(all->env, 0);
    while(copy[++i])
        copy = alph_sort(copy, i + 1);
    i = -1;
    while(copy[++i])
    {
        write(1,"\ndeclare -x ",13);
        j = -1;
        while(copy[i][++j])
            if(copy[i][j] == '=')
            {
                write(1,"=\"",3);
                write(1, (copy[i] + j + 1), ft_strlen(copy[i] + j + 1));
                write(1,"\"",1);
                break ;
            }
            else
                write(1,&copy[i][j], 1);
    }
    write(1,"\n",1);
    while(--i >= 0)
        free(copy[i]);
    free(copy);
}

int     help_export(t_all *all, int i, int j, int temp)
{

}

void check_export(t_all *all, int i, int len, char **copy)
{
    int j;
    int k;
    int temp;
    int nbr;

        i = -1;
        temp = -1;
		nbr = 0;
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
			temp = -1;
			nbr = check_for_value(all, i);
			while(all->env[++j])
			{
				temp = -1;
				while(all->data->args[i][++temp])
					{
						if(all->data->args[i][temp] == '=')
							break ;
						if(ft_isalnum(all->data->args[i][temp]) == 0)
						{
							// write(1,&all->data->args[i][temp], 1);
							temp = -2;
							break ;
						}
					}
				if ((all->data->args[i][0] <= '9' && all->data->args[i][0] >= '0') || temp == -2)
				{
						write(1, "minishell: export: ", 20);
						write(1,all->data->args[i], ft_strlen(all->data->args[i]));
						write(1,": not a valid identifier\n",26);
						// printf("minishell: export: %s: not a valid identifier", all->data->args[i]);
						g_error = 1;
					k = i;
					break ;
				}
				if (nbr != -1)
				{
					if(!ft_strncmp(all->data->args[i], all->env[j], nbr))
					{
						free(copy[j]);
						copy[j] = NULL;
						copy[j] = ft_strdup(all->data->args[i]);
						k = 0;
						break ;
					}
				}
			}
			if (k == -1 && nbr != -1)
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