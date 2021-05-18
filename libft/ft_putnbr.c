#include "libft.h"

void	put(long int *n, long int *b)
{
	if ((*n < 0))
	{
		*n *= -1;
		*b *= -1;
	}
}

void	ft_putnbr(long int n)
{
	long int	l;
	long int	v;
	char		c;

	l = 1;
	v = n;
	put(&v, &n);
	v /= 10;
	while (v > 0)
	{
		v /= 10;
		l *= 10;
	}
	while (l > 0)
	{
		v = n / l;
		c = v + 48;
		ft_putchar(c);
		if (v % l == 0)
			v = v / l;
		else
			n = n % l;
		l /= 10;
	}
}
