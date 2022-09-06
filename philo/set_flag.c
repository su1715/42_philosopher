/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_flag.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujpark <sujpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 17:16:07 by sujpark           #+#    #+#             */
/*   Updated: 2022/09/05 17:22:37 by sujpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_flag(pthread_mutex_t *mutex, int *flag)
{
	pthread_mutex_lock(mutex);
	*flag = 1;
	pthread_mutex_unlock(mutex);
}

void	set_last_eat(pthread_mutex_t *mutex_last_eat, t_timeval *last_eat)
{
	pthread_mutex_lock(mutex_last_eat);
	gettimeofday(last_eat, NULL);
	pthread_mutex_unlock(mutex_last_eat);
}
