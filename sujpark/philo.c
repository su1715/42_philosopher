/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujpark <sujpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 20:23:48 by sujpark           #+#    #+#             */
/*   Updated: 2022/09/05 15:48:20 by sujpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_eat(t_philo *philo)
{
	if (check_philo_die(philo))
		return ;
	set_last_eat(philo->mutex_last_eat, &philo->last_eat);
	philo_print(philo, "is_eating");
	ms_usleep(philo->args->time_to_eat);
}

void	*philo_sleep(t_philo *philo)
{
	if (check_philo_die(philo))
		return ;
	philo_print(philo, "is_sleeping");
	ms_usleep(philo->args->time_to_sleep);
}

void	*philo_think(t_philo *philo)
{
	if (check_philo_die(philo))
		return ;
	philo_print(philo, "is_thinking");
}

void	*run_philo(void *void_philo)
{
	// 포크들 변수로도 선언하기?
	t_philo	*philo;

	philo = (t_philo *)void_philo;
	while (!check_is_start(philo))
		;
	while (!check_philo_die(philo) && philo->args->n_of_must_eat != 0)
	{
		philo_lock_forks(philo);
		philo_eat(philo);
		philo_unlock_forks(philo);
		philo->cnt_eat++;
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}

void	init_philos(t_monitor *monitor)
{
	int		i;
	int		n_of_philo;
	t_philo	*philo;

	i = -1;
	n_of_philo = monitor->args->n_of_philo;
	while (++i < n_of_philo)
	{
		philo = &monitor->philos[i];
		philo->args = monitor->args;
		philo->index = i;
		philo->cnt_eat = 0;
		philo->is_die = &monitor->is_die;
		philo->is_start = &monitor->is_start;
		philo->mutex_is_die = &monitor->mutex_is_die;
		philo->mutex_is_start = &monitor->mutex_is_start;
		philo->mutex_print = &monitor->mutex_print;
		philo->mutex_last_eat = &monitor->mutex_last_eat[i];
		philo->fork_left = &monitor->mutex_forks[i];
		philo->fork_right = &monitor->mutex_forks[(i + 1) % n_of_philo];
		philo->start_time = &monitor->start_time;
	}
}

void	record_times(t_monitor *monitor)
{
	int		i;
	t_philo	philo;

	i = -1;
	gettimeofday(&monitor->start_time, NULL);
	while (++i < monitor->args->n_of_philo)
	{
		philo = monitor->philos[i];
		set_last_eat(&philo.mutex_last_eat, &philo.last_eat);
	}
}

void	run_philos(t_monitor *monitor)
{
	int			i;
	pthread_t	thread_philo;
	t_philo		philo;

	i = -1;
	while (++i < monitor->args->n_of_philo)
	{
		thread_philo = monitor->thread_philos[i];
		philo = monitor->philos[i];
		if (pthread_create(&thread_philo, NULL, run_philo, &philo))
			error_exit('thread_philo create error');
	}
}
