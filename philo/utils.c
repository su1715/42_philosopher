/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujpark <sujpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 15:58:37 by sujpark           #+#    #+#             */
/*   Updated: 2022/09/06 18:50:34 by sujpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

long	get_time_diff(t_timeval start_time)
{
	t_timeval	end_time;

	gettimeofday(&end_time, NULL);
	return (
		(end_time.tv_sec - start_time.tv_sec) * 1000
		+ (end_time.tv_usec - start_time.tv_usec) / 1000
	);
}

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
		usleep(250);
}
