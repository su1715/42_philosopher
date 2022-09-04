/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujpark <sujpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 14:23:26 by sujpark           #+#    #+#             */
/*   Updated: 2022/09/04 16:00:39 by sujpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct timeval	t_timeval;

typedef struct s_philo
{
	int				index;
	pthread_mutex_t	fork_left;
	pthread_mutex_t	fork_right;
}	t_philo;

typedef struct s_arguments
{
	int				n_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				n_of_must_eat;
}	t_arguments;

typedef struct s_monitor
{
	t_arguments		args;
	t_philo			*philo;
	pthread_mutex_t	*forks;
}	t_monitor;

/*utils.c*/
int	error_exit(char * str);
int	ft_isdigit(int c);

/*parse.c*/
t_arguments	*parse(int argc, char *argv[]);
# endif
