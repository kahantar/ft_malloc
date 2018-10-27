#include "includes/malloc.h"

int	ft_displayList(t_header *list)
{
	t_header *display;

	display = list;
	while(display)
	{
		ft_putnbr(display->size);
		ft_putchar('\n');
		ft_putnbr(display->is_free);
		ft_putchar('\n');
		display = display->next;
	}
	return(0);
}

int	ft_addInList(int size, t_header **list)
{
	t_header *new;

	if (!(new = malloc(sizeof(t_header))))
		return (0);
	new->is_free = 0;
	new->size = size;
	new->next = *list;
	*list = new;
	return (0);
}