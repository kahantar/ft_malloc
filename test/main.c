#include "includes/malloc.h"

int main()
{
    void* str;
    void* s;
    void* x;
    void* c;
    void* v;
    void* b;

    // ft_itoa_base(2147483648, 10);
    // ft_putnbr(2147483648);
    // ft_itoa_base(5550000 * 4096, 10);
    str = malloc(42073709551615);
    s = malloc(42073709551615);
    x = malloc(420);
    b = malloc(42);
    realloc(str, 10);
    realloc(s, 1000);
    realloc(b, 100000000000);
    realloc(x, 10);

    // 655299 * 4096
    // malloc(400);
    // free(str);
    // if (realloc(str, 111111111) == NULL)
        // ft_putstr("ok\n");
    show_alloc_mem();
    return (0);
}