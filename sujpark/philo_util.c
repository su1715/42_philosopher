/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujpark <sujpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 20:25:02 by sujpark           #+#    #+#             */
/*   Updated: 2022/09/05 21:13:54 by sujpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_lock_forks(t_philo *philo)
{
	if (philo->index % 2 == 0)
		pthread_mutex_lock(philo->fork_left);
	else
		pthread_mutex_lock(philo->fork_right);
	philo_print(philo, STATE_FORK);
	// if (check_fork_dup(philo))
	// 	return ;
	if (philo->index % 2 == 0)
		pthread_mutex_lock(philo->fork_right);
	else
		pthread_mutex_lock(philo->fork_left);
	philo_print(philo, STATE_FORK);
}

void	philo_unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);
}

void	philo_print(t_philo *philo, int state)
{
	char	*str;

	pthread_mutex_lock(philo->mutex_print);
	if (state && check_is_die(philo))
	{
		pthread_mutex_unlock(philo->mutex_print);
		return ;
	}
	str = get_state_str(state);
	printf("%04ld %d %s\n", \
			get_time_diff(*philo->start_time), philo->index, str);
	pthread_mutex_unlock(philo->mutex_print);
}

void	philo_increase_cnt_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->mutex_cnt_eat);
	philo->cnt_eat++;
	pthread_mutex_unlock(philo->mutex_cnt_eat);
}
