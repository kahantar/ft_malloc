/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahantar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 13:54:59 by kahantar          #+#    #+#             */
/*   Updated: 2018/12/21 19:49:17 by kahantar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

t_mutex		g_mutex;

void	search_alloc_large_free(void *ptr, t_header *list)
{
	t_header	*tmp;
	size_t		i;

	tmp = list;
	if (tmp && tmp->adresse == ptr)
	{
		g_glob.large_block = tmp->next;
		munmap(ptr, tmp->size);
	}
	else
	{
		while (tmp)
		{
			if (tmp->next->adresse == ptr)
			{
				if (list->next->next)
					list->next = list->next->next;
				else
					list->next = NULL;
				munmap(ptr, tmp->size);
			}
			list = list->next;
			tmp = list;
		}
	}
}

int		search_alloc_free(void *ptr, t_header *list)
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

void	free(void *ptr)
{
	if (pthread_mutex_lock(&g_mutex.m_free) == EINVAL)
	{
		pthread_mutex_init(&g_mutex.m_free, NULL);
		pthread_mutex_lock(&g_mutex.m_free);
	}
	if (ptr != NULL)
	{
		if (!search_alloc_free(ptr, g_glob.tiny_block))
		{
			if (!search_alloc_free(ptr, g_glob.small_block))
				search_alloc_large_free(ptr, g_glob.large_block);
		}
	}
	pthread_mutex_unlock(&g_mutex.m_free);
}
