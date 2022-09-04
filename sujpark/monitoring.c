/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujpark <sujpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 16:12:24 by sujpark           #+#    #+#             */
/*   Updated: 2022/09/04 22:53:57 by sujpark          ###   ########.fr       */
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

void	monitor_init(t_monitor *monitor)
{
	int	i;
	monitor_mutex_init(monitor);
	monitor->is_die = 0;
	philos_init(monitor);
	set_is_start(&monitor->mutex_is_start, &monitor->is_start);
	run_philos(monitor);
	set_is_not_start(&monitor->mutex_is_start, &monitor->is_start);
}

void	monitor_malloc(t_monitor *monitor, void *args)
{
	int	n_of_philo;

	monitor->args = (t_arguments *)args;
	n_of_philo = monitor->args->n_of_philo;
	monitor->thread_philos = ft_calloc(n_of_philo, sizeof(pthread_t));
	monitor->philos = ft_calloc(n_of_philo, sizeof(t_philo));
	monitor->mutex_cnt_eat = ft_calloc(n_of_philo, sizeof(pthread_mutex_t));
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
		i = ++i % monitor->args->n_of_philo;
		if (check_philo_last_eat(monitor, &monitor->philos[i]) \ // 여기 고치기
			|| check_philos_must_eat(monitor))
		{
			// 그리고 여기부터
			philo_print(&monitor->philos[i % monitor->args->n_of_philo], \
																"is died\n");
			pthread_mutex_lock(&monitor->mutex_print); // unlock은 ?
			set_die_mutex_flag(monitor->mutex_is_die, monitor->is_die);
			break ;
		}
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
