#include "includes/malloc.h"

int     check_block(t_header *list)
{
    while(list)
    {
        if (list->is_free == 1)
            return (1);
        list = list->next;
    }
    return (0);
}

void    put_block(t_header *list, char *str)
{
    if (check_block(list))
    {
        ft_putstr(str);
        ft_putstr(" : ");
        ft_itoa_base(list, 16);
        ft_putchar('\n');
        while(list)
        {
            if (list->is_free == 1)
            {
                ft_itoa_base(list + 1, 16);
                ft_putstr(" - ");
                ft_itoa_base((void*)list + 32 + list->size, 16);
                ft_putstr(" : ");
                ft_putnbr(list->size);
                ft_putstr(" octets\n");
            }
            list = list->next;
        }
    }
}

void    show_alloc_mem()
{
    put_block(glob.tiny_block, "TINY");
    put_block(glob.small_block, "SMALL");
    put_block(glob.large_block, "LARGE");
}