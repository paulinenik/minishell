#include "mshell.h"
#include <unistd.h>

void	sigint(int num)
{
	(void)num;
	write(1, "\n", 2);
}

void	sigquit(int num)
{
	(void)num;
	write(1, "Quit: 3\n", 9);
}

void	sigint2(int num)
{
	(void)num;
}

void	sigquit2(int num)
{
	(void)num;
}
