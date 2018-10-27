#ifndef MALLOC_H
# define MALLOC_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/mman.h>

# define SIZE_TINY  256
# define SIZE_SMALL 4096
# define TRUE_TINY  256 - sizeof(t_header)
# define TRUE_SMALL 4096 - sizeof(t_header)
# define BLOCKS     112


typedef struct s_header {
    void                *adresse;
    size_t             size;
    unsigned int    is_free;
    struct s_header *next;
}                   t_header;

typedef struct s_block {
    t_header            *tiny_block;
    t_header            *small_block;
    t_header            *large_block;
}                   t_block;

typedef enum		e_type
{
	TINY,
	SMALL,
	LARGE
}					t_type;

extern t_block             glob;


int                 ft_addInList(int size, t_header **list);
int                 ft_displayList(t_header *list);
void                *malloc(size_t size);
void                ft_putnbr(int n);
void                ft_putchar(char c);
void	            ft_putstr(char const *s);
void                free(void *ptr);
void                ft_itoa_base(size_t n, int base);
size_t	            ft_strlen(const char *str);
void    *realloc(void *ptr, size_t size);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void    show_alloc_mem();



#endif