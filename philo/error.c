/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujpark <sujpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 22:10:17 by sujpark           #+#    #+#             */
/*   Updated: 2022/09/05 22:29:10 by sujpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args_too_big(t_arguments	*args)
{
	if (args->n_of_philo == TOO_BIG)
		return (1);
	if (args->time_to_die == TOO_BIG)
		return (1);
	if (args->time_to_eat == TOO_BIG)
		return (1);
	if (args->time_to_sleep == TOO_BIG)
		return (1);
	if (args->n_of_must_eat == TOO_BIG)
		return (1);
	return (0);
}

int	check_allocate_monitor_error(t_monitor *monitor)
{
	return (
		!monitor->thread_philos
		|| !monitor->philos
		|| !monitor->mutex_cnt_eat
		|| !monitor->mutex_forks
		|| !monitor->mutex_last_eat
	);
}

void	print_error(char *str)
{
	printf("%s\n", str);
}
