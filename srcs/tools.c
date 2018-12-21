/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahantar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 22:28:53 by kahantar          #+#    #+#             */
/*   Updated: 2018/12/22 00:01:35 by kahantar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void		initialize_block(void)
{
	g_glob.tiny_block = NULL;
	g_glob.small_block = NULL;
	g_glob.large_block = NULL;
}

t_header	*load_zone(void *memory, int shift, size_t size)
{
	t_header	*list;
	t_header	*tmp;
	t_header	*ret;
	int			i;

	if (memory == NULL)
		return (NULL);
	i = 0;
	list = memory;
	ret = list;
	while (i < BLOCKS)
	{
		list->size = size;
		list->is_free = 0;
		list->adresse = (void*)list + sizeof(t_header);
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

t_header	*load_zone_large(void *memory, size_t size)
{
	t_header	*ret;
	size_t		size_zone;

	if (memory == NULL)
		return (NULL);
	if (!(ret = (t_header*)search(g_glob.tiny_block, sizeof(t_header)\
					, TINY, 8)))
		return (NULL);
	if ((size % 4096) == 0)
		size_zone = size;
	else
		size_zone = ((size / 4096) + 1) * 4096;
	ret->adresse = memory;
	ret->is_free = 0;
	ret->size = size_zone;
	ret->next = NULL;
	return (ret);
}

t_header	*create_block(size_t size)
{
	void *memory;

	memory = mmap(0, size, PROT_READ | PROT_WRITE\
			, MAP_ANON | MAP_PRIVATE, -1, 0);
	if (memory == (void*)-1)
		return (NULL);
	return (memory);
}
