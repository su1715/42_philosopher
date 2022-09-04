/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujpark <sujpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 15:58:37 by sujpark           #+#    #+#             */
/*   Updated: 2022/09/04 16:40:03 by sujpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error_exit(char * str)
{
	perror(str);
	exit(1);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

void	*ft_memset(void *ptr, int value, size_t num)
{
	unsigned char	*ptr_c;
	size_t			i;

	ptr_c = (unsigned char *)ptr;
	i = 0;
	while (i < num)
	{
		ptr_c[i] = (unsigned char)value;
		i++;
	}
	return ((void *)ptr);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = malloc(count * size);
	if (!ptr)
		error_exit("calloc error");
	ft_memset(ptr, 0, count * size);
	return (ptr);
}
