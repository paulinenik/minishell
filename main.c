#include <term.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft/libft.h"
#include <string.h>
#include <stdio.h>
#include "mshell.h"

char	**init(char **envp, int k)
{
	int		i;
	int		j;
	char	**new;
	
	i = 0;
	j = -1;
	while(envp[i])
		i++;
	new = malloc((i + 1 + k) * sizeof(char *));
	new[i + k] = NULL;
	while (++j < i)
		new[j] = ft_strdup(envp[j]);
	return (new);
}

void	path_init(t_all *all)
{
	int i;
	char *str;
	
	i = -1;
	str = get_var_value(all->env,"HOME");
	all->home_path = ft_strdup(str);
	// while(all->home_path[++i])
	// 	printf("%c",all->home_path[i]);
}

void	print_in_file(char *str,t_all *all)
{
	//fd = open(f, O_RDWR);
  	write(all->fd, str, ft_strlen(str));
	write(all->fd,"\n", 1);
  //	close(all->fd);
}

void	create_history(t_all *all, char *str)
{
	int		i;
	char	**copy;

	i = -1;
	if(ft_strcmp(str,""))
	{
		all->size += 1;
		if (all->commands_hist == NULL)
		{
			all->fd = open("./bash.txt", O_RDWR);
			all->commands_hist = malloc(sizeof(char *) * 2);
			all->commands_hist[0] = ft_strdup(str);
			all->commands_hist[1] = NULL;
			print_in_file(str, all);
		}
		else
		{
			while(all->commands_hist[++i]);
			copy = init(all->commands_hist, 1);
			copy[i] = ft_strdup(str);
			print_in_file(str, all);
			copy[i + 1] = NULL;
			i++;
			while(--i >= 0)
				free(all->commands_hist[i]);
			free(all->commands_hist);
			all->commands_hist = copy;
			// i = -1;
			// while(all->commands_hist[++i])
			// 	printf("\n my command -%s-\n", all->commands_hist[i]);
		}
	}
}

int     main(int argc, char **argv, char **envp)
{
	printf("%d\n", ft_strncmp("ab","ab=", 3));
	(void)argc;
	(void)argv;
	g_error = 0;
	char	buf[101];
	t_all	*all;
	struct	termios	term;
	struct	termios	term1;
	int l;
	char *term_name = "xterm-256color";
	char	*input;
	input = NULL;
	int len = 0;

	all = (t_all *)malloc(sizeof(t_all));
	all->env = init(envp, 0);
	all->data = NULL;
	all->commands_hist = NULL;
	all->size = 0;
	path_init(all);
	tcgetattr(0, &term);
	tcgetattr(0, &term1);
	term.c_lflag &= ~(ECHO);
	term.c_lflag &= ~(ICANON);
	term.c_lflag &= ~(ISIG);
	tcsetattr(0, TCSANOW, &term);
	// term.c_cc[VMIN] = 1;
	// term.c_cc[VTIME] = 0;
	tgetent(0, term_name);
		int i = 0;
	//	int len = 0;
	 while(ft_strncmp(buf, "\4", 2))
	{
		term.c_lflag &= ~(ECHO);
		term.c_lflag &= ~(ICANON);
		term.c_lflag &= ~(ISIG);
		tcsetattr(0, TCSANOW, &term);
		write(1, "\033[36;1mminishell$\033[0m ", 23);
		tputs(save_cursor, 1, ft_putchar);
		i = 0;
		do
		{
		 	l = read(0, buf, 100);
			buf[l] = 0;
			if(!ft_strncmp(buf,"\e[A",4))
			{
				tputs(restore_cursor, 1, ft_putchar);
				while (--i > 0)
					tputs(tgetstr("dc", 0), 1, ft_putchar);
				if(all->commands_hist != NULL)
				{
				if (all->size > 0)
					all->size--;
				write(1,all->commands_hist[all->size],ft_strlen(all->commands_hist[all->size]));
				i = ft_strlen(all->commands_hist[all->size]);
				if (input != NULL)
					free(input);
				input = NULL;
				int l = -1;
				while(all->commands_hist[all->size][++l])
					input = add_char(input, all->commands_hist[all->size][l]);
			}
			}
			else if(!ft_strncmp(buf,"\e[B", 4))
			{
				tputs(restore_cursor, 1, ft_putchar);
				while (--i > 0)
					tputs(tgetstr("dc", 0), 1, ft_putchar);
				if(all->commands_hist != NULL)
				{
					if (all->commands_hist[all->size + 1])
						all->size++;
					write(1,all->commands_hist[all->size],ft_strlen(all->commands_hist[all->size]));
					i = ft_strlen(all->commands_hist[all->size]);
					if (input != NULL)
						free(input);
					input = NULL;
					int l = -1;
					while(all->commands_hist[all->size][++l])
						input = add_char(input, all->commands_hist[all->size][l]);
				}
			}
			else if(!ft_strncmp(buf, "\177", 2))
			{
				if (i > 0)
				{
					tputs(cursor_left, 1, ft_putchar);
					tputs(tgetstr("dc", 0), 1, ft_putchar);
					input = delete_char(input);
					i--;
				}
			}
			else if(!ft_strncmp(buf, "\e[D", 4))
			{
				if (i > 0)
				{
					tputs(cursor_left, 1, ft_putchar);
					i--;
				}
			}
			else if(!ft_strncmp(buf, "\e[C", 4))
			{
				if (i < (int)ft_strlen(input))
				{
					tputs(cursor_right, 1, ft_putchar);
					i++;
				}
			}
			else if(!ft_strncmp(buf, "\3", 2))
			{
				write(1,"\n",1);
				input = add_char(input, '\n');
				break ;
			}
			else if(!ft_strncmp(buf, "\4", 2))
			{
				write (1, "exit\n", 6);
				term = term1;
				tcsetattr(0, TCSANOW, &term);
				exit (0);
			}
			else 
			{
				if (*buf != '\n')
					input = add_char(input, *buf);
				write (1, buf, 1);
				i++;
			}
		} while (ft_strncmp(buf, "\n", 1));
		term = term1;
		tcsetattr(0, TCSANOW, &term);
		input = add_char(input, '\0');
		create_history(all, input);
		parse(input, all);
		if (input != NULL)
			free(input);
		input = NULL;
		clear_all(&all->data);
	}
	write(1,"\n", 1);
	close(all->fd);
	return (0);
}