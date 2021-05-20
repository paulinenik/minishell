#include "mshell.h"
#include "libft.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

void	print_in_file(char *str, t_all *all)
{
	write(all->fd, str, ft_strlen(str));
	write(all->fd, "\n", 1);
}

void	help_to_create(t_all *all, int i, char **copy, char *str)
{
	while (all->commands_hist[++i])
		;
	copy = init(all->commands_hist, 1);
	copy[i] = ft_strdup(str);
	print_in_file(str, all);
	copy[i + 1] = NULL;
	i++;
	while (--i >= 0)
		free(all->commands_hist[i]);
	free(all->commands_hist);
	all->commands_hist = copy;
	all->amount = -1;
	while (all->commands_hist[++all->amount])
		;
}

void	create_history(t_all *all, char *str)
{
	int		i;
	char	**copy;

	copy = NULL;
	i = -1;
	if (ft_strcmp(str, ""))
	{
		all->size += 1;
		if (all->commands_hist == NULL)
		{
			all->fd = open("./bash.txt", O_RDWR);
			all->commands_hist = malloc(sizeof(char *) * 2);
			if (!all->commands_hist)
				return ;
			all->commands_hist[0] = ft_strdup(str);
			all->commands_hist[1] = NULL;
			print_in_file(str, all);
			all->amount = 1;
		}
		else
			help_to_create(all, i, copy, str);
	}
}
