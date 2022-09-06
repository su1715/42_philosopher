/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujpark <sujpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 20:25:02 by sujpark           #+#    #+#             */
/*   Updated: 2022/09/06 10:58:10 by sujpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

int	check_one_philo(t_philo *philo)
{
	if (philo->mutex_fork_left == philo->mutex_fork_right)
	{
		ms_usleep(philo->args->time_to_die + 100);
		pthread_mutex_unlock(philo->mutex_fork_left);
		return (1);
	}
	return (0);
}
