/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahantar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 15:08:06 by kahantar          #+#    #+#             */
/*   Updated: 2018/11/12 15:08:30 by kahantar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

int		ft_strcmp(const char *s1, const char *s2)
{
	int	n;

	n = 0;
	while (s1[n] == s2[n] && s1[n] != '\0' && s2[n] != '\0')
	{
		n++;
	}
	return ((unsigned char)s1[n] - (unsigned char)s2[n]);
}
