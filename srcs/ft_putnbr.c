#include "includes/malloc.h"

void	ft_putnbr(int n)
{
	long int	i;

	i = n;
	if (i == 0)
		ft_putchar(48);
	if (i < 0 && i >= -2147483648)
	{
		ft_putchar('-');
		i = -i;
	}
	if (i >= 10 && i <= 2147483648)
	{
		ft_putnbr(i / 10);
		ft_putnbr(i % 10);
	}
	if (i > 0 && i < 10)
	{
		ft_putchar('0' + i);
	}
}