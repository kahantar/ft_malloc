/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahantar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 15:21:00 by kahantar          #+#    #+#             */
/*   Updated: 2018/12/21 23:57:59 by kahantar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

t_block		g_glob;
t_mutex		g_mutex;

t_header	*after_search(int shift, t_type type, size_t size)
{
	if (type == TINY)
		return (load_zone(create_block(SIZE_TINY * BLOCKS),\
					shift, TRUE_TINY));
	else if (type == SMALL)
		return (load_zone(create_block(SIZE_SMALL * BLOCKS),\
						shift, TRUE_SMALL));
	else
		return (load_zone_large(create_block(size), size));
}

void		*search(t_header *list, size_t size, t_type type, int shift)
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
			list->next = after_search(shift, type, size);
		list = list->next;
	}
	return (NULL);
}

void		*malloc_large(size_t size)
{
	if (g_glob.large_block == NULL)
		g_glob.large_block = load_zone_large(create_block(size), size);
	return (search(g_glob.large_block, size, LARGE, 0));
}

void		*malloc_small(size_t size)
{
	if (g_glob.small_block == NULL)
	{
		g_glob.small_block = load_zone(create_block(SIZE_SMALL * BLOCKS)\
				, 128, TRUE_SMALL);
	}
	return (search(g_glob.small_block, size, SMALL, 128));
}

void		*malloc(size_t size)
{
	void	*ret;

	if (pthread_mutex_lock(&g_mutex.m_malloc) == EINVAL)
	{
		pthread_mutex_init(&g_mutex.m_malloc, NULL);
		pthread_mutex_lock(&g_mutex.m_malloc);
	}
	if (!g_glob.tiny_block && !g_glob.small_block && !g_glob.large_block)
		initialize_block();
	if (size <= TRUE_TINY)
	{
		if (g_glob.tiny_block == NULL)
		{
			g_glob.tiny_block = load_zone(create_block(SIZE_TINY * BLOCKS)\
					, 8, TRUE_TINY);
		}
		ret = (search(g_glob.tiny_block, size, TINY, 8));
	}
	else if (size <= TRUE_SMALL)
		ret = malloc_small(size);
	else
		ret = malloc_large(size);
	pthread_mutex_unlock(&g_mutex.m_malloc);
	return (ret);
}
