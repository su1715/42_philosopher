/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujpark <sujpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 15:58:37 by sujpark           #+#    #+#             */
/*   Updated: 2022/09/05 15:56:48 by sujpark          ###   ########.fr       */
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

long	get_time_diff(t_timeval start_time)
{
	t_timeval	end_time;
	long		end_time_int;
	long		start_time_int;

	gettimeofday(&end_time, NULL);
	end_time_int = \
			(long)((end_time.tv_sec * 1000) + (end_time.tv_usec / 1000));
	start_time_int = \
			(long)((start_time.tv_sec * 1000) + (start_time.tv_usec / 1000));
	return (end_time_int - start_time_int);
}
