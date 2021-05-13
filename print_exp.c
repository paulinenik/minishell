#include "mshell.h"

void print_export(t_all *all, int i, int j)
{
    char    **copy;
    
    copy = init(all->env, 0);
    while (copy[++i])
        copy = alph_sort(copy, i + 1);
    i = -1;
    while (copy[++i])
    {
        write(1, "\ndeclare -x ",13);
        j = -1;
        while (copy[i][++j])
            if (copy[i][j] == '=')
            {
                write(1, "=\"",3);
                write(1, (copy[i] + j + 1), ft_strlen(copy[i] + j + 1));
                write(1, "\"",1);
                break ;
            }
            else
                write(1,&copy[i][j], 1);
    }
    write(1, "\n",1);
    while (--i >= 0)
        free(copy[i]);
    free(copy);
}

 int     help_export(t_all *all, int i, int j, char **copy)
 {
    write(1, "hmeee",5);
    free(copy[j]);
    copy[j] = NULL;
    copy[j] = ft_strdup(all->data->args[i]);
    return (0);
 }

int     help2_export(t_all *all, int i, int j, int nbr)
{
    int k;

    k = -1;
    if (nbr == -1 && !ft_scmp(all->data->args[i], all->env[j],'='))
    {
        write(1, "here",5);
        k = 0;
        if (check_for_value(all, j, -1) != -1 && ((int)ft_strlen(all->data->args[i]) > check_for_value(all, j, -1)))
        {
            return (-1);
        }
        
    }
    return (k);
}

void    exp_cor(t_all *all, char **copy, int nbr, int i)
{
    int k;
    int j;

    j = -1;
    while (all->env[++j])
    {
        k = alnum_search(all->data->args, i, -1, -2);
        if (k == 0)
            break ;
        if (nbr != -1 && (!ft_strncmp(all->env[j],all->data->args[i], nbr + 1) ||
        ft_strncmp(all->data->args[i],all->env[j], ft_strlen(all->data->args[i]) + 1) == 61))
        {
            k = help_export(all, i, j, copy);
            break ;
        }
        k = help2_export(all, i, j, nbr);
    }
    if (k == -1)
    {
        write(1, "HELLO",6);
        copy[all->len_env] = ft_strdup(all->data->args[i]);
        all->len_env++;
    }
}

void check_export(t_all *all, int i, int k, int j)
{
        char **copy;
        int nbr;
        
        j = -1;
        i = -1;
		nbr = 0;
		while (all->data->args[++i]);
		while (all->env[++j]);
		all->len_env = j;
		k = save_index(all->data, all->env);
		copy = init(all->env, i - k);
		i = -1;
		while (all->data->args[++i])
		{
			nbr = check_for_value(all, i, 0);
            exp_cor(all, copy, nbr, i);
		}
		copy[all->len_env] = NULL;
		while (--j >= 0)
		   free(all->env[j]);
		free(all->env);
		all->env = copy;
    }

				