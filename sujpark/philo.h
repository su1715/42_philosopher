/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujpark <sujpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 14:23:26 by sujpark           #+#    #+#             */
/*   Updated: 2022/09/04 20:26:26 by sujpark          ###   ########.fr       */
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

typedef struct s_arguments
{
	int				n_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				n_of_must_eat;
}	t_arguments;

typedef struct s_philo
{
	int				index;
	int				*is_die;
	pthread_mutex_t	*mutex_is_die;
	pthread_mutex_t	*mutex_print;
	pthread_mutex_t	*mutex_last_eat;
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;
	t_timeval		*start_time;
	t_timeval		last_eat;
}	t_philo;

typedef struct s_monitor
{
	t_timeval		start_time;
	pthread_t		*thread_philos;
	t_philo			*philos;
	t_arguments		*args;

	int				is_die;
	pthread_mutex_t	*mutex_forks;
	pthread_mutex_t	*mutex_last_eat;
	pthread_mutex_t	mutex_is_die;
	pthread_mutex_t	mutex_print;
	pthread_mutex_t	mutex_start;
}	t_monitor;

/* utils.c */
int	error_exit(char * str);
int	ft_isdigit(int c);
void	*ft_calloc(size_t count, size_t size);

/* parse.c */
t_arguments	*parse(int argc, char *argv[]);

/* monitoring.c */
void	monitoring(t_arguments *args);

/* philo.c */
void	philos_init(t_monitor *monitor);
void	run_philos(t_monitor *monitor);

/* mutex.c */
void	set_last_eat(pthread_mutex_t *mutex_last_eat, t_timeval *last_eat);

# endif
