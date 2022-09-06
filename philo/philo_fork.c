/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_fork.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujpark <sujpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 10:58:12 by sujpark           #+#    #+#             */
/*   Updated: 2022/09/06 18:44:12 by sujpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_get_fork(pthread_mutex_t *mutex_fork, int *fork)
{
	pthread_mutex_lock(mutex_fork);
	*fork = 1;
}

void	philo_put_down_fork(pthread_mutex_t *mutex_fork, int *fork)
{
	*fork = 0;
	pthread_mutex_unlock(mutex_fork);
}

void	philo_lock_forks(t_philo *philo)
{
	if (philo->index % 2 == 0)
		philo_get_fork(philo->mutex_fork_left, philo->fork_left);
	else
		philo_get_fork(philo->mutex_fork_right, philo->fork_right);
	philo_print(philo, STATE_FORK);
	if (check_one_philo(philo))
		return ;
	if (philo->index % 2 == 0)
		philo_get_fork(philo->mutex_fork_right, philo->fork_right);
	else
		philo_get_fork(philo->mutex_fork_left, philo->fork_left);
	philo_print(philo, STATE_FORK);
}

void	philo_unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->mutex_fork_left);
	pthread_mutex_unlock(philo->mutex_fork_right);
}
