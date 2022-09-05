/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujpark <sujpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 20:25:02 by sujpark           #+#    #+#             */
/*   Updated: 2022/09/05 13:31:23 by sujpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_last_eat(pthread_mutex_t *mutex_last_eat, t_timeval *last_eat)
{
	pthread_mutex_lock(mutex_last_eat);
	gettimeofday(last_eat, NULL);
	pthread_mutex_unlock(mutex_last_eat);
}

void	set_is_start(pthread_mutex_t *mutex_is_start, int *is_start)
{
	pthread_mutex_lock(mutex_is_start);
	*is_start = 1;
	pthread_mutex_unlock(mutex_is_start);
}

void	set_is_not_start(pthread_mutex_t *mutex_is_start, int *is_start)
{
	pthread_mutex_lock(mutex_is_start);
	*is_start = 0;
	pthread_mutex_unlock(mutex_is_start);
}

int	check_is_die(pthread_mutex_t *mutex_is_die, int is_die)
{
	int	die;

	pthread_mutex_lock(mutex_is_die);
	die = is_die;
	pthread_mutex_unlock(mutex_is_die);
	return (die);
}

void	philo_lock_forks(t_philo *philo)
{
	if (philo->index % 2 == 0)
		pthread_mutex_lock(philo->fork_right);
	else
		pthread_mutex_lock(philo->fork_left);
	philo_print(philo, "has taken a fork \n");
	// if (check_fork_dup(philo))
	// 	return ;
	if (philo->index % 2 == 0)
		pthread_mutex_lock(philo->fork_left);
	else
		pthread_mutex_lock(philo->fork_right);
	philo_print(philo, "has taken a fork \n");
}

void	philo_unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);
}

void	philo_print(t_philo *philo, char *strs)
{
	pthread_mutex_lock(philo->mutex_print);
	if (check_philo_die(philo))
	{
		pthread_mutex_unlock(philo->mutex_print);
		return ;
	}
	printf("%04ld %d %s\n", get_diff_time(*philo->start_time), philo->index, strs);
	pthread_mutex_unlock(philo->mutex_print);
}

int	check_philo_starve(t_monitor *monitor, t_philo *philo)
{
	t_timeval	last_eat;
	int			time_to_die;
	int			is_starve;

	is_starve = 0;
	last_eat = philo->last_eat;
	time_to_die = monitor->args->time_to_die;
	pthread_mutex_lock(monitor->mutex_last_eat);
	if (get_diff_time(last_eat) >= time_to_die)
		is_starve = 1;
	pthread_mutex_unlock(monitor->mutex_last_eat);
	return (is_starve);
}

int	check_philos_must_eat(t_monitor *monitor)
{
	int	i;
	int	all_eat;

	i = -1;
	all_eat = 1;
	while(++i < monitor->args->n_of_philo)
	{
		pthread_mutex_lock(&monitor->mutex_cnt_eat[i]);
		if (monitor->args->n_of_must_eat > monitor->philos[i].cnt_eat)
			all_eat = 0;
		pthread_mutex_unlock(&monitor->mutex_cnt_eat[i]);
	}
	return (all_eat);
}

void	set_is_die(pthread_mutex_t *mutex_is_die, int is_die)
{
	pthread_mutex_lock(mutex_is_die);
	is_die = 1;
	pthread_mutex_unlock(mutex_is_die);
}
