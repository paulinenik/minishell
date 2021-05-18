#include "mshell.h"

void	ft_signal_cltr_c(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	g_exit_status[0] = 1;
	ft_print_shell();
}

static	void	ft_signal_quit(int sig)
{
	write(1, "\b\b  \b\b", 6);
	write(1, "^\\Quit: ", 8);
	ft_putnbr(sig, 1);
	write(1, "\n", 1);
}