/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujpark <sujpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 16:12:24 by sujpark           #+#    #+#             */
/*   Updated: 2022/09/06 12:22:58 by sujpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_philo_end(t_monitor *monitor, t_philo *philo)
{
	if (check_philo_starve(monitor, philo))
	{
		set_flag(&monitor->mutex_is_die, &monitor->is_die);
		philo_print(philo, STATE_DIE);
		return (1);
	}
	if (check_philos_must_eat(monitor))
	{
		set_flag(&monitor->mutex_is_die, &monitor->is_die);
		return (1);
	}
	return (0);
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
		if (check_philo_end(monitor, &monitor->philos[i]))
			break ;
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
