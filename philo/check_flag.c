/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_flag.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujpark <sujpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 17:20:46 by sujpark           #+#    #+#             */
/*   Updated: 2022/09/06 14:37:20 by sujpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_flag(pthread_mutex_t *mutex, int *flag)
{
	int	temp;

	pthread_mutex_lock(mutex);
	temp = *flag;
	pthread_mutex_unlock(mutex);
	return (temp);
}

int	check_is_start(t_philo *philo)
{
	return (check_flag(philo->mutex_is_start, philo->is_start));
}

int	check_is_die(t_philo *philo)
{
	return (check_flag(philo->mutex_is_die, philo->is_die));
}

int	check_philo_starve(t_monitor *monitor, t_philo *philo)
{
	t_timeval	last_eat;
	int			time_to_die;
	int			is_starve;

	is_starve = 0;
	pthread_mutex_lock(monitor->mutex_last_eat);
	last_eat = philo->last_eat;
	pthread_mutex_unlock(monitor->mutex_last_eat);
	time_to_die = monitor->args->time_to_die;
	if (get_time_diff(last_eat) > time_to_die)
		is_starve = 1;
	return (is_starve);
}

int	check_philos_must_eat(t_monitor *monitor)
{
	int	i;
	int	all_eat;

	if (monitor->args->n_of_must_eat == -1)
		return (0);
	i = -1;
	all_eat = 1;
	while (++i < monitor->args->n_of_philo)
	{
		pthread_mutex_lock(&monitor->mutex_cnt_eat[i]);
		if (monitor->args->n_of_must_eat > monitor->philos[i].cnt_eat)
			all_eat = 0;
		pthread_mutex_unlock(&monitor->mutex_cnt_eat[i]);
	}
	return (all_eat);
}
