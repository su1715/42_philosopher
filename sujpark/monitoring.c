/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujpark <sujpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 16:12:24 by sujpark           #+#    #+#             */
/*   Updated: 2022/09/05 16:22:49 by sujpark          ###   ########.fr       */
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

void	init_monitor(t_monitor *monitor)
{
	monitor->is_die = 0;
	monitor->is_start = 0;
	monitor_mutex_init(monitor);
	init_philos(monitor);
	run_philos(monitor);
	record_times(monitor);
	set_is_start(&monitor->mutex_is_start, &monitor->is_start);
}

t_monitor	*allocate_monitor(t_monitor *monitor, void *args)
{
	t_monitor	*monitor;
	int			n_of_philo;

	monitor = ft_calloc(1, sizeof(t_monitor));
	monitor->args = (t_arguments *)args;
	n_of_philo = monitor->args->n_of_philo;
	monitor->thread_philos = ft_calloc(n_of_philo, sizeof(pthread_t));
	monitor->philos = ft_calloc(n_of_philo, sizeof(t_philo));
	monitor->mutex_cnt_eat = ft_calloc(n_of_philo, sizeof(pthread_mutex_t));
	monitor->mutex_forks = ft_calloc(n_of_philo, sizeof(pthread_mutex_t));
	monitor->mutex_last_eat = ft_calloc(n_of_philo, sizeof(pthread_mutex_t));
	return (monitor);
}

void	*run_monitor(void *args)
{
	t_monitor	*monitor;
	int			i;

	i = -1;
	monitor = allocate_monitor(monitor, args);
	init_monitor(monitor);
	while (1)
	{
		i = ++i % monitor->args->n_of_philo;
		if (check_philo_starve(monitor, &monitor->philos[i])
			|| check_philos_must_eat(monitor))
		{
			philo_print(&monitor->philos[i], "is died");
			pthread_mutex_lock(&monitor->mutex_print);
			set_is_die(&monitor->mutex_is_die, monitor->is_die);
			pthread_mutex_unlock(&monitor->mutex_print);
			break ;
		}
	}
	clean_up(monitor);
	return (NULL); // 꼭 반환?
}


void	monitoring(t_arguments *args)
{
	pthread_t	thread_monitor;

	if (pthread_create(&thread_monitor, NULL, run_monitor, args))
		error_exit('thread_monitor create error');
	if (pthread_join(thread_monitor, NULL) != 0)
		return ; // 에러처리 해야하나?
}
