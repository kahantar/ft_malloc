/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahantar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 15:40:01 by kahantar          #+#    #+#             */
/*   Updated: 2018/12/21 19:23:50 by kahantar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

t_mutex		g_mutex;

void		*search_alloc_realloc(void *ptr, size_t size, t_header *list)
{
	void	*ret;

	while (list)
	{
		if (list->adresse == ptr)
		{
			if (!(ret = malloc(size)))
				return (NULL);
			if (size < list->size)
				ft_memcpy(ret, ptr, size);
			else
				ft_memcpy(ret, ptr, list->size);
			free(ptr);
			return (ret);
		}
		list = list->next;
	}
	return (NULL);
}

void		*realloc(void *ptr, size_t size)
{
	void *ret;

	if (size <= 0)
		return (NULL);
	if (pthread_mutex_lock(&g_mutex.m_realloc) == EINVAL)
	{
		pthread_mutex_init(&g_mutex.m_realloc, NULL);
		pthread_mutex_lock(&g_mutex.m_realloc);
	}
	if (ptr == NULL)
	{
		pthread_mutex_unlock(&g_mutex.m_realloc);
		return (malloc(size));
	}
	ret = search_alloc_realloc(ptr, size, g_glob.tiny_block);
	if (ret == NULL)
		ret = search_alloc_realloc(ptr, size, g_glob.small_block);
	if (ret == NULL)
		ret = search_alloc_realloc(ptr, size, g_glob.large_block);
	pthread_mutex_unlock(&g_mutex.m_realloc);
	return (ret);
}
