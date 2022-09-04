/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujpark <sujpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 20:23:48 by sujpark           #+#    #+#             */
/*   Updated: 2022/09/04 20:27:11 by sujpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philos_init(t_monitor *monitor)
{
	int		i;
	int		n_of_philo;
	t_philo	*philo;

	i = -1;
	n_of_philo = monitor->args->n_of_philo;
	while (++i < n_of_philo)
	{
		philo = &monitor->philos[i];
		philo->index = i;
		philo->is_die = &monitor->is_die;
		philo->mutex_is_die = &monitor->mutex_is_die;
		philo->mutex_print = &monitor->mutex_print;
		philo->mutex_last_eat = &monitor->mutex_last_eat[i];
		philo->fork_left = &monitor->mutex_forks[i];
		philo->fork_right = &monitor->mutex_forks[(i + 1) % n_of_philo];
		philo->start_time = &monitor->start_time;
	}
}

void	*run_philo(void *void_philo)
{
	t_philo	*philo;
	int		eat_count;

	philo = (t_philo *)void_philo;
	eat_count = 0;
	// if (philo->index % 2 == 0)
	// 	ms_usleep(philo->args->time_to_eat * 0.1);
	while (check_philo_die(philo) == 0 && philo->eat_count != 0)
	{
		philo_lock_forks(philo);
		philo_action_and_print(philo, "is eating\n", TIME_TO_EAT);
		philo_unlock_forks(philo);
		eat_count++;
		if (eat_count == philo->eat_count)
			up_count_all_eat_mutex_flag(philo->all_eat_mutex, \
													philo->all_eat_count);
		philo_action_and_print(philo, "is sleeping\n", TIME_TO_SLEEP);
		philo_action_and_print(philo, "is thinking\n", 0);
	}
	return (NULL);
}

void	run_philos(t_monitor *monitor)
{
	int	i;
	int	n_of_philo;

	i = -1;
	n_of_philo = monitor->args->n_of_philo;
	while (++i < n_of_philo)
		if (pthread_create(&monitor->thread_philos[i], NULL, run_philo, \
		&monitor->philos[i]))
			error_exit('thread_philo create error');

	i = -1;
	while (++i < n_of_philo)
		set_last_eat(&monitor->philos[i].mutex_last_eat, \
							&monitor->philos[i].last_eat);
	gettimeofday(&monitor->start_time, NULL);
}
