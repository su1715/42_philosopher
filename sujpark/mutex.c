/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujpark <sujpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 20:25:02 by sujpark           #+#    #+#             */
/*   Updated: 2022/09/04 20:25:08 by sujpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_last_eat(pthread_mutex_t *mutex_last_eat, t_timeval *last_eat)
{
	pthread_mutex_lock(mutex_last_eat);
	gettimeofday(last_eat, NULL);
	pthread_mutex_unlock(mutex_last_eat);
}
