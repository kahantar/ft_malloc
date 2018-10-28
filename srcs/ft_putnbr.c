#include "../includes/malloc.h"

void	ft_putnbr(size_t n)
{
	size_t	i;

	i = (size_t)n;
	if (i == 0)
		ft_putchar(48);
	// if (i < 0 && i >= -2147483648)
	// {
		// ft_putchar('-');
		// i = -i;
	// }
	if (i >= 10 && i <= 18446744073709551615)
	{
		ft_putnbr(i / 10);
		ft_putnbr(i % 10);
	}
	if (i > 0 && i < 10)
	{
		ft_putchar('0' + i);
	}
}