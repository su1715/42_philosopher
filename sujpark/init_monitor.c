/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_monitor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujpark <sujpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 11:57:36 by sujpark           #+#    #+#             */
/*   Updated: 2022/09/06 12:21:21 by sujpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	mutex_init_wrapper(pthread_mutex_t *mutex)
{
	return (pthread_mutex_init(mutex, NULL));
}

int	init_monitor_vars(t_monitor *monitor)
{
	int	i;
	int	stat;

	i = -1;
	stat = 0;
	monitor->is_die = 0;
	monitor->is_start = 0;
	while (++i < monitor->args->n_of_philo)
	{
		monitor->forks[i] = 0;
		stat |= mutex_init_wrapper(&monitor->mutex_cnt_eat[i]);
		stat |= mutex_init_wrapper(&monitor->mutex_forks[i]);
		stat |= mutex_init_wrapper(&monitor->mutex_last_eat[i]);
	}
	stat |= mutex_init_wrapper(&monitor->mutex_is_die);
	stat |= mutex_init_wrapper(&monitor->mutex_print);
	stat |= mutex_init_wrapper(&monitor->mutex_is_start);
	return (stat);
}

int	init_monitor(t_monitor *monitor)
{
	if (init_monitor_vars(monitor))
	{
		clean_monitor(monitor);
		print_error("init monitor var error");
		return (1);
	}
	init_philos(monitor);
	if (run_philos(monitor))
	{
		clean_monitor(monitor);
		print_error("run philo error");
		return (1);
	}
	record_times(monitor);
	set_flag(&monitor->mutex_is_start, &monitor->is_start);
	return (0);
}

t_monitor	*allocate_monitor(void *args)
{
	t_monitor	*monitor;
	int			n_of_philo;

	monitor = malloc(sizeof(t_monitor));
	if (!monitor)
		return (NULL);
	monitor->args = (t_arguments *)args;
	n_of_philo = monitor->args->n_of_philo;
	monitor->thread_philos = malloc(n_of_philo * sizeof(pthread_t));
	monitor->philos = malloc(n_of_philo * sizeof(t_philo));
	monitor->forks = malloc(n_of_philo * sizeof(int));
	monitor->mutex_cnt_eat = malloc(n_of_philo * sizeof(pthread_mutex_t));
	monitor->mutex_forks = malloc(n_of_philo * sizeof(pthread_mutex_t));
	monitor->mutex_last_eat = malloc(n_of_philo * sizeof(pthread_mutex_t));
	if (check_allocate_monitor_error(monitor))
	{
		free_monitor(monitor);
		return (NULL);
	}
	return (monitor);
}
