# include <stdlib.h>
# include <unistd.h>

void        ft_base(size_t n, int base, int i)
{
    char str[i];

    str[i] = '\0';
    while (--i >= 2)
    {
        if (n % base > 9)
            str[i] = 'A' - 10 + (n % base);
        else
            str[i] = (n % base) + 48;
        n = n / base;
    }
    str[0] = '0';
    str[1] = 'x';
    write(1, str, ft_strlen(str));
}

void        ft_itoa_base(size_t n, int base)
{
	size_t		x;
	int			i;

	i = 1;
	x = n;
	while (x >= base)
	{
		x = x / base;
		i++;
	}
	ft_base(n, base, i);
}

