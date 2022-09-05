/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujpark <sujpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 20:47:12 by sujpark           #+#    #+#             */
/*   Updated: 2022/09/05 20:47:42 by sujpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	*get_state_str(int state)
{
	char	*str;

	str = NULL;
	if (state == STATE_DIE)
		str = "is died";
	else if (state == STATE_FORK)
		str = "has taken a fork";
	else if (state == STATE_EAT)
		str = "is eating";
	else if (state == STATE_SLEEP)
		str = "is sleeping";
	else if (state == STATE_THINK)
		str = "is thinking";
	return (str);
}

void	ms_usleep(int ms_second)
{
	t_timeval	start_time;

	gettimeofday(&start_time, NULL);
	while (get_time_diff(start_time) < ms_second)
		usleep(500);
}
