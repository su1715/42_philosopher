/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujpark <sujpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 14:23:26 by sujpark           #+#    #+#             */
/*   Updated: 2022/09/05 21:51:57 by sujpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

# define STATE_DIE 0
# define STATE_FORK 1
# define STATE_EAT 2
# define STATE_SLEEP 3
# define STATE_THINK 4

typedef struct timeval	t_timeval;

typedef struct s_arguments
{
	int				n_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				n_of_must_eat;
}			t_arguments;

typedef struct s_philo
{
	t_arguments		*args;
	int				index;
	int				cnt_eat;
	int				*is_die;
	int				*is_start;
	pthread_mutex_t	*mutex_is_die;
	pthread_mutex_t	*mutex_is_start;
	pthread_mutex_t	*mutex_print;
	pthread_mutex_t	*mutex_cnt_eat;
	pthread_mutex_t	*mutex_last_eat;
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;
	t_timeval		*start_time;
	t_timeval		last_eat;
}			t_philo;

typedef struct s_monitor
{
	t_timeval		start_time;
	pthread_t		*thread_philos;
	t_philo			*philos;
	t_arguments		*args;

	int				is_die;
	int				is_start;
	pthread_mutex_t	*mutex_cnt_eat;
	pthread_mutex_t	*mutex_forks;
	pthread_mutex_t	*mutex_last_eat;
	pthread_mutex_t	mutex_is_die;
	pthread_mutex_t	mutex_print;
	pthread_mutex_t	mutex_is_start;
}			t_monitor;

/* utils.c */
int			error_exit(char *str);
int			ft_isdigit(int c);
void		*ft_calloc(size_t count, size_t size);
long		get_time_diff(t_timeval start_time);

/* utils2.c */
char		*get_state_str(int state);
void		ms_usleep(int ms_second);

/* parse.c */
t_arguments	*parse(int argc, char *argv[]);

/* monitoring.c */
void		monitoring(t_arguments *args);

/* philo.c */
void		init_philos(t_monitor *monitor);
void		run_philos(t_monitor *monitor);
void		record_times(t_monitor *monitor);

/* philo_util.c */
void		philo_lock_forks(t_philo *philo);
void		philo_unlock_forks(t_philo *philo);
void		philo_print(t_philo *philo, int state);
void		philo_increase_cnt_eat(t_philo *philo);

/* set_flag.c */
void		set_flag(pthread_mutex_t *mutex, int *flag);
void		set_last_eat(pthread_mutex_t *mutex_last_eat, t_timeval *last_eat);

/* get_flag.c */
int			check_is_start(t_philo *philo);
int			check_is_die(t_philo *philo);
int			check_philo_starve(t_monitor *monitor, t_philo *philo);
int			check_philos_must_eat(t_monitor *monitor);

/* philo_action.c */
void		philo_eat(t_philo *philo);
void		philo_sleep(t_philo *philo);
void		philo_think(t_philo *philo);

/* free.c */
void		clean_up(t_monitor *monitor);
# endif

/*
[o] 파일 정리
[o] 로직 확인
[o] 함수 이름 변경
[o] makefile
[] 누수확인
[] 주석제거
[] norminette
[] 헤더 체크
[] perror, exit 빼기
[] 1명 예외처리
[o] cnt_eat mutex 처리
[o] index 1 부터~
[o] 재우기 (쥐는 방향과 시작 번호 고려)
*/
