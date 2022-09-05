/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujpark <sujpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 16:12:24 by sujpark           #+#    #+#             */
/*   Updated: 2022/09/05 22:47:24 by sujpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	monitor_mutex_init(t_monitor *monitor)
{
	int	i;

	i = -1;
	while (++i < monitor->args->n_of_philo)
	{
		pthread_mutex_init(&monitor->mutex_cnt_eat[i], NULL);
		pthread_mutex_init(&monitor->mutex_forks[i], NULL);
		pthread_mutex_init(&monitor->mutex_last_eat[i], NULL);
	}
	pthread_mutex_init(&monitor->mutex_is_die, NULL);
	pthread_mutex_init(&monitor->mutex_print, NULL);
	pthread_mutex_init(&monitor->mutex_is_start, NULL);
}

int	init_monitor(t_monitor *monitor)
{
	monitor->is_die = 0;
	monitor->is_start = 0;
	monitor_mutex_init(monitor);
	init_philos(monitor);
	if (run_philos(monitor))
	{
		destroy_mutexes(monitor);
		free_monitor(monitor);
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
	monitor->mutex_cnt_eat = malloc(n_of_philo * sizeof(pthread_mutex_t));
	monitor->mutex_forks = malloc(n_of_philo * sizeof(pthread_mutex_t));
	monitor->mutex_last_eat = malloc(n_of_philo * sizeof(pthread_mutex_t));
	if (check_allocate_monitor_error(monitor))
	{
		free(monitor);
		return (NULL);
	}
	return (monitor);
}

void	*run_monitor(void *args)
{
	t_monitor	*monitor;
	int			i;

	i = -1;
	monitor = allocate_monitor(args);
	if (!monitor)
	{
		print_error("allocate_monitor error");
		return (NULL);
	}
	if (init_monitor(monitor))
		return (NULL);
	while (1)
	{
		i = (i + 1) % monitor->args->n_of_philo;
		if (check_philo_starve(monitor, &monitor->philos[i])
			|| check_philos_must_eat(monitor))
		{
			set_flag(&monitor->mutex_is_die, &monitor->is_die);
			philo_print(&monitor->philos[i], STATE_DIE);
			break ;
		}
	}
	clean_up(monitor);
	return (NULL);
}

void	monitoring(t_arguments *args)
{
	pthread_t	thread_monitor;

	if (pthread_create(&thread_monitor, NULL, run_monitor, args))
	{
		print_error("thread_monitor create error");
		return ;
	}
	pthread_join(thread_monitor, NULL);
}
