#include "includes/malloc.h"

void    *search_alloc_realloc(void *ptr, size_t size, t_header *list)
{
    void    *ret;

    while (list)
    {
        if (list + 1 == ptr)
        {
            if (list->size >= size)
                return (ptr);
            else
            {
                if (!(ret = malloc(size)))
                    return NULL;
                ft_memcpy(ret, ptr, list->size);
                free(ptr);
            }
            return (ret);
        }
        list = list->next;
    }
    return NULL;
}

void    *realloc(void *ptr, size_t size)
{
    void *ret;
    if (size <= 0)
        return NULL;
    if (ptr == NULL)
        return (malloc(size));
    ret = search_alloc_realloc(ptr, size, glob.tiny_block);
    if (ret == NULL)
        ret = search_alloc_realloc(ptr, size, glob.small_block);
    if (ret == NULL)
        ret = search_alloc_realloc(ptr, size, glob.large_block);
    return ret;
}
