#include "../includes/malloc.h"

t_mutex             mutex;

void    *search_alloc_realloc(void *ptr, size_t size, t_header *list)
{
    void    *ret;
    while (list)
    {
        if (list->adresse == ptr)
        {
            if (!(ret = malloc(size)))
                return NULL;
            if (size < list->size)
                ft_memcpy(ret, ptr, size);
            else
                ft_memcpy(ret, ptr, list->size);
            free(ptr);
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
    if (pthread_mutex_lock(&mutex.m_realloc) == EINVAL)
    {
        pthread_mutex_init(&mutex.m_realloc, NULL);
        pthread_mutex_lock(&mutex.m_realloc);
    }
    if (ptr == NULL){
        pthread_mutex_unlock(&mutex.m_realloc);
        return (malloc(size));
    }
    ret = search_alloc_realloc(ptr, size, glob.tiny_block);
    if (ret == NULL)
        ret = search_alloc_realloc(ptr, size, glob.small_block);
    if (ret == NULL)
        ret = search_alloc_realloc(ptr, size, glob.large_block);
    pthread_mutex_unlock(&mutex.m_realloc);
    return ret;
}
