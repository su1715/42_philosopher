/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujpark <sujpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 22:02:29 by kipark            #+#    #+#             */
/*   Updated: 2022/09/04 16:39:16 by sujpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*pointer;

	i = 0;
	pointer = (unsigned char *)b;
	while (i < len)
	{
		pointer[i] = (unsigned char)c;
		++i;
	}
	return ((void *)pointer);
}


void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = malloc(count * size);
	if (ptr == 0)
		print_error(1);
	ft_memset(ptr, -1, count * size);
	return (ptr);
}
