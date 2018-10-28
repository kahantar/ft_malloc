#include "../includes/malloc.h"


void    ft_base(size_t n, int base, int i)
{
	char str[i];

    str[i] = '\0';
	if (base <= 10)
	{
		while (--i >= 0)
		{
			str[i] = (n % base) + 48;
			n = n / base;
		}
	}
	if (base > 10)
	{
		while (--i >= 0)
		{
			if (n % base > 9)
				str[i] = 'a' - 10 + (n % base);
			else
				str[i] = (n % base) + 48;
			n = n / base;
		}
	}
	ft_putstr(str);
}

void    ft_itoa_base(size_t n, int base)
{
	size_t		x;
	int			i;

	i = 1;
	x = n;
    if (base == 16)
        ft_putstr("0x");
	while (x >= (size_t)base)
	{
		x = x / base;
		i++;
	}
	(ft_base(n, base, i));
}
