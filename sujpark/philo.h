/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujpark <sujpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 14:23:26 by sujpark           #+#    #+#             */
/*   Updated: 2022/09/05 16:01:05 by sujpark          ###   ########.fr       */
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
	t_arguments		*args;//init
	int				index;//init
	int				cnt_eat;//init 0
	int				*is_die;//init
	int				*is_start;//init
	pthread_mutex_t	*mutex_is_die;//init
	pthread_mutex_t	*mutex_is_start;//init
	pthread_mutex_t	*mutex_print;//init
	pthread_mutex_t	*mutex_last_eat;//init
	pthread_mutex_t	*fork_left;//init
	pthread_mutex_t	*fork_right;//init
	t_timeval		*start_time;//init
	t_timeval		last_eat;//philo thread 전부 생성된 후 init
}	t_philo;

typedef struct s_monitor
{
	t_timeval		start_time;//philo thread 전부 생성된 후 init
	pthread_t		*thread_philos;//malloc
	t_philo			*philos;//malloc
	t_arguments		*args;//malloc

	int				is_die; // init 0
	int				is_start; // init 0
	pthread_mutex_t *mutex_cnt_eat;//malloc // init
	pthread_mutex_t	*mutex_forks;//malloc // init
	pthread_mutex_t	*mutex_last_eat;//malloc // init
	pthread_mutex_t	mutex_is_die;//init
	pthread_mutex_t	mutex_print;//init
	pthread_mutex_t	mutex_is_start;//init
}	t_monitor;

/* utils.c */
int		error_exit(char * str);
int		ft_isdigit(int c);
void	*ft_calloc(size_t count, size_t size);
long	get_time_diff(t_timeval start_time);

/* parse.c */
t_arguments	*parse(int argc, char *argv[]);

/* monitoring.c */
void	monitoring(t_arguments *args);

/* philo.c */
void	init_philos(t_monitor *monitor);
void	run_philos(t_monitor *monitor);
void	record_times(t_monitor *monitor);

/* mutex.c */
void	set_last_eat(pthread_mutex_t *mutex_last_eat, t_timeval *last_eat);
void	set_is_start(pthread_mutex_t *mutex_is_start, int *is_start);
int		check_is_die(pthread_mutex_t *mutex_is_die, int is_die);
void	philo_lock_forks(t_philo *philo);
void	philo_unlock_forks(t_philo *this_philo);
void	philo_print(t_philo *philo, char *strs);
int		check_philo_starve(t_monitor *monitor, t_philo *philo);
int		check_philos_must_eat(t_monitor *monitor);
void	set_is_die(pthread_mutex_t *mutex_is_die, int is_die);
int		check_is_start(t_philo *philo);

/* free.c */
void	clean_up(t_monitor *monitor);
# endif

/*
[] 파일 정리
[] 로직 확인
[] 함수 이름 변경
[] makefile
[] 디버깅
[] 누수확인
[] 의문 해결하기
[] 주석제거
[] norminette
[] 헤더 체크
[] static 붙일까?
// args는 동시 접근.. 읽기만하는데 data race일까?
*/
