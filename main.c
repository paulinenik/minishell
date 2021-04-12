#include <term.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include <string.h>
#include <stdio.h>
#include "mshell.h"

int     get_next_line(char **line)
{
	char	buf[10000];
	int		b_read;
	int		i;

	if (((i = 0) && read(0, &buf[i], 0) < 0) || !(line))
		return (-1);
	while ((b_read = read(0, &buf[i], 1)) > 0 && buf[i] != '\n')
		i++;
	buf[i] = '\0';
	if (b_read != -1 && (*line = malloc((i + 1) * sizeof(char))))
	{
		i = -1;
		while (buf[++i])
			(*line)[i] = buf[i];
		(*line)[i] = '\0';
	}
	return (b_read);
}

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


int     main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	char	buf[101];
	char	**new;
	// char	**test;
	t_all	*all;
	struct	termios	term;
	int l;
	char *term_name = "xterm-256color";
	char	*input;
	input = NULL;

	all = (t_all *)malloc(sizeof(t_all));
	all->env = init(envp, 0);
	all->data = NULL;
	// int i = -1;
	// while(new[++i])
	// 	printf("%s\n", new[i]);
	tcgetattr(0, &term);
	term.c_lflag &= ~(ECHO);
	term.c_lflag &= ~(ICANON);
	tcsetattr(0, TCSANOW, &term);
	// term.c_cc[VMIN] = 1;
	// term.c_cc[VTIME] = 0;
	tgetent(0, term_name);
	// test = malloc((3) * sizeof(char*));
	// for(int j = 0; j < 3; j++)
	// {
	// 	test[j] = malloc(3+1);
	// }
	// unsigned char c;
	// for (int i = 0; i < 2; i++) {
    //     for (int j = 0; j < 3; j++) {
    //         printf("Enter your value.\n");
    //         scanf("%c", &c);
    //         test[i][j] = c;
    //     }
    // }
		// test[0] = "ASC\0";
		// test[1] = "ASE\0";
		// test[2] = NULL;
		//printf("%s\n%s\n",test[0],test[1]);
		int i = 0;
	 while(ft_strncmp(buf, "\4", 2))
	{
		write(1, "minishell$ ", 12);
		tputs(save_cursor, 1, ft_putchar);
		do
		{
		 	l = read(0, buf, 100);
			buf[l] = 0;
			if(!ft_strncmp(buf,"\e[A",4))
			{
				tputs(restore_cursor, 1, ft_putchar);
				tputs(tigetstr("ed"), 1, ft_putchar);
				write(1,"next",4);
			}
			else if(!ft_strncmp(buf,"\e[B", 4))
			{
				tputs(restore_cursor, 1, ft_putchar);
				tputs(tigetstr("ed"), 1, ft_putchar);
				write(1,"back",4);
			}
			else if(!ft_strncmp(buf, "\177", 2))
			{
				tputs(cursor_left, 1, ft_putchar);
				tputs(tigetstr("ed"), 1, ft_putchar);
			}
			else
			{
				input = add_char(input, *buf);
				write (1, buf, 1);
			}
		} while (ft_strncmp(buf, "\n", 1) && ft_strncmp(buf, "\4", 1));
		input = add_char(input, '\0');
		parse(input, all);
		free(input);
		input = NULL;
		// get_pwd(data);
		// get_export(data);

		// test = NULL;
		i++;
	 }
	 write(1,"\n", 1);
	return (0);
}