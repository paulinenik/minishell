#include "mshell.h"

void move_right(char *input, int *i)
{
    if (i < (int)ft_strlen(input))
    {
        tputs(cursor_right, 1, ft_putchar);
        (*i)++;
    }
}

void move_left(char *input, int *i)
{
    if (i > 0)
    {
        tputs(cursor_left, 1, ft_putchar);
        (*i)--;
    }
}

void ctrl_D(struct	termios	term, struct termios term1)
{
    write (1, "exit\n", 6);
    term = term1;
    tcsetattr(0, TCSANOW, &term);
    exit (0);
}

void ctrl_C(char *input, int *i, char *buf)
{
    *buf = '\n';
    write(1,"\n",1);
    input = add_char(input, '\n');
}

void usual_cap(char *input, int *i, char *buf)
{
    if (*buf != '\n')
        input = add_char(input, *buf);
    write (1, buf, 1);
    i++;
}