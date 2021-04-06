#include <term.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft/libft.h"
#include <string.h>

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
	return (b_read > 0 ? 1 : b_read);
}

int     main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	char	buf[10000];
	struct	termios	term;
	int l;
	char *term_name = "xterm-256color";

	tcgetattr(0, &term);
	term.c_lflag &= ~(ECHO);
	term.c_lflag &= ~(ICANON);
	tcsetattr(0, TCSANOW, &term);
	// term.c_cc[VMIN] = 1;
	// term.c_cc[VTIME] = 0;
	tgetent(0, term_name);
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
			else if(!strcmp(buf, key_backspace) && !strcmp(buf,"\177"))
			{
				tputs(cursor_left, 1, ft_putchar);
				tputs(tigetstr("ed"), 1, ft_putchar);
			}
			else
				write (1, buf, l);
			
		} while (ft_strncmp(buf, "\n", 1) && ft_strncmp(buf, "\4", 2));

	 }
	return (0);
}