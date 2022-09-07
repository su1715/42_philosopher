/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujpark <sujpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 17:28:12 by sujpark           #+#    #+#             */
/*   Updated: 2022/09/06 18:47:33 by sujpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_philo *philo)
{
	set_last_eat(philo->mutex_last_eat, &philo->last_eat);
	if (check_is_die(philo))
		return ;
	philo_print(philo, STATE_EAT);
	ms_usleep(philo->args->time_to_eat);
}

void	philo_sleep(t_philo *philo)
{
	if (check_is_die(philo))
		return ;
	philo_print(philo, STATE_SLEEP);
	ms_usleep(philo->args->time_to_sleep);
}

void	philo_think(t_philo *philo)
{
	long	left;

	if (check_is_die(philo))
		return ;
	philo_print(philo, STATE_THINK);
	if (philo->args->n_of_philo % 2 == 1)
	{
		left = philo->args->time_to_die - get_time_diff(philo->last_eat);
		if (left > 0)
			ms_usleep(left * 0.6);
	}
}
