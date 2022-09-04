/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujpark <sujpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 20:25:02 by sujpark           #+#    #+#             */
/*   Updated: 2022/09/04 22:09:26 by sujpark          ###   ########.fr       */
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

int	check_is_die(pthread_mutex_t *mutex_is_die, int *is_die)
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

void	philo_print(t_philo *philo, char *strs) // 공부
{
	pthread_mutex_lock(philo->mutex_print);
	if (check_philo_die(philo))
		return;
	printf("%04ld %d %s\n", get_diff_time(*philo->start_time), philo->index, strs);
	pthread_mutex_unlock(philo->mutex_print);
}
