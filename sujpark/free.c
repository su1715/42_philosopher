/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujpark <sujpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 13:56:43 by sujpark           #+#    #+#             */
/*   Updated: 2022/09/06 12:20:40 by sujpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	join_thread_philos(t_monitor *monitor)
{
	int	i;

	i = -1;
	while (++i < monitor->args->n_of_philo)
		pthread_join(monitor->thread_philos[i], NULL);
}

void	destroy_mutexes(t_monitor *monitor)
{
	int	i;

	i = -1;
	while (++i < monitor->args->n_of_philo)
	{
		pthread_mutex_destroy(&monitor->mutex_cnt_eat[i]);
		pthread_mutex_destroy(&monitor->mutex_forks[i]);
		pthread_mutex_destroy(&monitor->mutex_last_eat[i]);
	}
	pthread_mutex_destroy(&monitor->mutex_is_die);
	pthread_mutex_destroy(&monitor->mutex_print);
	pthread_mutex_destroy(&monitor->mutex_is_start);
}

void	free_monitor(t_monitor *monitor)
{
	free(monitor->args);
	free(monitor->philos);
	free(monitor->thread_philos);
	free(monitor->forks);
	free(monitor->mutex_cnt_eat);
	free(monitor->mutex_forks);
	free(monitor->mutex_last_eat);
	free(monitor);
}

void	clean_monitor(t_monitor *monitor)
{
	destroy_mutexes(monitor);
	free_monitor(monitor);
}

void	clean_up(t_monitor *monitor)
{
	join_thread_philos(monitor);
	clean_monitor(monitor);
}
