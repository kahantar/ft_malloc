#include "../includes/malloc.h"


int     search_alloc_large_free(void *ptr, t_header *list)
{
    t_header *tmp;
    
    tmp = list;
    size_t i;

    if (tmp && tmp->adresse == ptr)
    {
        i = tmp->size;
        glob.large_block = tmp->next;
        munmap(ptr, i);
    }
    else{
        while (tmp)
        {
            if (tmp->next->adresse == ptr)
            {
                i = tmp->size;
                if (list->next->next)
                    list->next = list->next->next;
                else
                    list->next = NULL;
                munmap(ptr, i);
            }
            list = list->next;
            tmp = list;
        }
    }
    return (0);
}

int     search_alloc_free(void *ptr, t_header *list)
{
    while (list)
    {
        if (list + 1 == ptr)
        {
            list->is_free = 0;
            return (1);
        }
        list = list->next;
    }
    return (0);
}

void    free(void *ptr)
{

    if (ptr != NULL)
        if (!search_alloc_free(ptr, glob.tiny_block))
            if (!search_alloc_free(ptr, glob.small_block))
                search_alloc_large_free(ptr, glob.large_block);
}