#include "includes/malloc.h"

t_block             glob;

void	ft_putchar(char c)
{
	write(1, &c, 1);
}
t_header    *load_zone(void *memory, int shift, size_t size)
{
    t_header *list;
    t_header *tmp;
    t_header *ret;
    int i;

    if (memory == NULL)
        return NULL;
    i = 0;
    list = memory;
    ret = list;
    while(i < BLOCKS)
    {
        list->size = size;
        list->is_free = 0;
        list->adresse = (void*)list + size + sizeof(t_header);
        if (i == BLOCKS - 1)
            tmp = NULL;
        else
            tmp = list + shift;
        list->next = tmp;
        list = list->next;
        i++;
    }
    return (ret);
}

t_header    *load_zone_large(void *memory, size_t size)
{
    t_header *ret;
    int      size_zone;

    if (memory == NULL)
        return NULL;
    ret = memory;
    if ((size % 4096) == 0){
        size_zone = size;
    }
    else{
        size_zone = ((size / 4096) + 1) * 4096;
    }
    ret->adresse = memory + size_zone;
    ret->is_free = 0;
    ret->size = size_zone - sizeof(t_header);
    ret->next = NULL;
    return (ret);
}

t_header    *create_block(size_t size)
{

    void *memory;

    memory = mmap(0, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
    if (memory == (void*) -1)
		return NULL;
    return memory;
}

void    initializeBlock()
{
    glob.tiny_block = NULL;
    glob.small_block = NULL;
    glob.large_block = NULL;
}

void *search_zone_free(t_header *list, size_t size, t_type type, int shift)
{
    t_header *tmp;
    tmp = list;
    while (list)
    {
        if (list->is_free == 0 && list->size >= size)
        {
            list->is_free = 1;
            return ((void *)(list + 1));
        }
        if (list->next == NULL)
        {
            if (type == TINY)
                list->next = load_zone(create_block(SIZE_TINY * BLOCKS), shift, TRUE_TINY);
            else if (type == SMALL)
                list->next = load_zone(create_block(SIZE_SMALL * BLOCKS), shift, TRUE_SMALL);
            else
                list->next = load_zone_large(create_block(size + sizeof(t_header)), size + sizeof(t_header));
        }
        list = list->next;   
    }
    return NULL;
}

void *malloc(size_t size)
{
    if (size <= 0)
        return NULL;
    if (!glob.tiny_block && !glob.small_block && !glob.large_block){
        initializeBlock();
    }
    if (size <= TRUE_TINY)
    {
        if(glob.tiny_block == NULL)
            glob.tiny_block = load_zone(create_block(SIZE_TINY * BLOCKS), 8, TRUE_TINY);
        return(search_zone_free(glob.tiny_block, size, TINY, 8));
    }
    else if (size <= TRUE_SMALL)
    {
        if(glob.small_block == NULL)
            glob.small_block = load_zone(create_block(SIZE_SMALL * BLOCKS), 128, TRUE_SMALL);
        return(search_zone_free(glob.small_block, size, SMALL, 128));
    }
    if(glob.large_block == NULL){ 
        glob.large_block = load_zone_large(create_block(size + sizeof(t_header)), size + sizeof(t_header));
    }
    return (search_zone_free(glob.large_block, size, LARGE, 0));
}