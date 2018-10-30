void *search_zone_free(t_header *list, size_t size, t_type type, int shift)
{
    t_header *tmp;
    tmp = list;
   
    while (list)
    {
        if (list->is_free == 0 && list->size >= size)
        {
            list->is_free = 1;
            if (type == LARGE)
                return ((list->adresse));
            else
                return ((void *)(list + 1));
        }
        if (list->next == NULL)
        {
            if (type == TINY)
                list->next = load_zone(create_block(SIZE_TINY * BLOCKS), shift, TRUE_TINY);
            else if (type == SMALL)
                list->next = load_zone(create_block(SIZE_SMALL * BLOCKS), shift, TRUE_SMALL);
            else
                list->next = load_zone_large(create_block(size), size);
        }
        list = list->next;   
    }
    return NULL;
}
