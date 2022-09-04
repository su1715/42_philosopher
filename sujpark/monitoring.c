/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujpark <sujpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 16:12:24 by sujpark           #+#    #+#             */
/*   Updated: 2022/09/04 20:24:58 by sujpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	monitor_mutex_init(t_monitor *monitor)
{
	int	i;

	i = -1;
	while (++i < monitor->args->n_of_philo)
	{
		pthread_mutex_init(&monitor->mutex_forks[i], NULL);
		pthread_mutex_init(&monitor->mutex_last_eat[i], NULL);
	}
	pthread_mutex_init(&monitor->mutex_is_die, NULL);
	pthread_mutex_init(&monitor->mutex_print, NULL);
	pthread_mutex_init(&monitor->mutex_start, NULL);
}

void	monitor_init(t_monitor *monitor)
{
	int	i;
	monitor_mutex_init(monitor);
	monitor->is_die = 0;
	philos_init(monitor);
	pthread_mutex_lock(&monitor->mutex_start);
	run_philos(monitor);
	pthread_mutex_unlock(&monitor->mutex_start);
}

void	monitor_malloc(t_monitor *monitor, void *args)
{
	int	n_of_philo;

	monitor->args = (t_arguments *)args;
	n_of_philo = monitor->args->n_of_philo;
	monitor->thread_philos = ft_calloc(n_of_philo, sizeof(pthread_t));
	monitor->philos = ft_calloc(n_of_philo, sizeof(t_philo));
	monitor->mutex_forks = ft_calloc(n_of_philo, sizeof(pthread_mutex_t));
	monitor->mutex_last_eat = ft_calloc(n_of_philo, sizeof(pthread_mutex_t));
}

static void	*run_monitor(void *args)
{
	t_monitor		*monitor;
	unsigned int	i;

	monitor = malloc(sizeof(t_monitor)); // 수정
	monitor_malloc(monitor, args);
	monitor_init(monitor);
	i = -1;
	while (1)
	{
		// if (check_philo_last_eat(monitor, \
		// 	&monitor->philosophers[++i % monitor->all_philo_number].last_eat, \
		// 	monitor->get_parse[TIME_TO_DIE]) || \
		// 	check_count_all_eat_mutex_flag(monitor->all_eat_mutex, \
		// 	monitor->all_eat_count, monitor->all_philo_number))
		// {
		// 	philo_print(&monitor->philosophers[i % monitor->all_philo_number], \
		// 														"is died\n");
		// 	pthread_mutex_lock(monitor->print_mutex);
		// 	set_die_mutex_flag(monitor->die_mutex, monitor->die_flag);
		// 	break ;
		// }
	}
	//philo_wait_and_free(monitor);
	return (NULL); // 꼭 반환?
}


void	monitoring(t_arguments *args)
{
	pthread_t	thread_monitor;

	if (pthread_create(&thread_monitor, NULL, run_monitor, args))
		error_exit('thread_monitor create error');
	if (pthread_join(thread_monitor, NULL) != 0) // join ?
		return ;
}
