#include "../includes/malloc.h"
t_mutex             mutex;

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

void    put_block_large(t_header *list, char *str)
{
    if (check_block(list))
    {
        ft_putstr(str);
        ft_putstr(" : ");
        ft_itoa_base((size_t)list->adresse, 16);
        ft_putchar('\n');
        while(list)
        {
            if (list->is_free == 1)
            {
                ft_itoa_base((size_t)list->adresse, 16);
                ft_putstr(" - ");
                ft_itoa_base((size_t)list->adresse + list->size, 16);
                ft_putstr(" : ");
                ft_itoa_base((size_t)list->size, 10);
                ft_putstr(" octets\n");
            }
            list = list->next;
        }
    }
}

void    put_block(t_header *list, char *str)
{
    if (check_block(list))
    {
        ft_putstr(str);
        ft_putstr(" : ");
        ft_itoa_base((size_t)list, 16);
        ft_putchar('\n');
        while(list)
        {
            if (list->is_free == 1)
            {
                ft_itoa_base((size_t)list + 32, 16);
                ft_putstr(" - ");
                ft_itoa_base((size_t)list + 32 + list->size, 16);
                ft_putstr(" : ");
                ft_itoa_base((size_t)list->size, 10);
                ft_putstr(" octets\n");
            }
            list = list->next;
        }
    }
}

void    show_alloc_mem()
{
    if (pthread_mutex_lock(&mutex.m_show_alloc_mem) == EINVAL)
    {
        pthread_mutex_init(&mutex.m_show_alloc_mem, NULL);
        pthread_mutex_lock(&mutex.m_show_alloc_mem);
    }
    put_block(glob.tiny_block, "TINY");
    put_block(glob.small_block, "SMALL");
    put_block_large(glob.large_block, "LARGE");
    pthread_mutex_unlock(&mutex.m_show_alloc_mem);

}