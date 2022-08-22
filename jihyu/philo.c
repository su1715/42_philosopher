/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujpark <sujpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 15:20:18 by jihyukim          #+#    #+#             */
/*   Updated: 2022/08/22 16:27:42 by sujpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead(t_philo *philo)
{
	int	dead;

	pthread_mutex_lock(&(philo->info->check_death));
	dead = philo->info->is_dead;
	pthread_mutex_unlock(&(philo->info->check_death)); // 이부분 코드 겹치지 않나? 어차피 whil문에서도 매번 검사할텐데
	if (dead) // 이미 죽은 경우
		return (1);
	else if (philo->info->t_die < get_time() - philo->t_last_eat) // 먹은 후 경과시간이 죽는시간보다 크면
	{
		prints(philo->info, get_time() - philo->info->t_start, philo->id, DIE); // 나 죽는다 프린트
		pthread_mutex_lock(&(philo->info->check_death));
		philo->info->is_dead = 1;
		pthread_mutex_unlock(&(philo->info->check_death));
		return (1);
	}
	return (0);
}

int	philo_eat(t_info *info, t_philo *philo)
{
	if (is_dead(philo)) // 죽었는지 확인 // 여기서도?
		return (1);
	pthread_mutex_lock(&info->fork[philo->left]); // 홀수는 왼쪽부터 짝수는 오른쪽부터 안하시나..? 짝수먼저 먹으면 상관 없나?
	prints(info, get_time() - info->t_start, philo->id, FORK);
	if (info->n_philo == 1) // 철학자 한명인 경우
	{
		pthread_mutex_unlock(&(info->fork[philo->left]));
		psleep(info->t_die);
		prints(info, get_time() - info->t_start, philo->id, DIE);
		return (1);
	}
	pthread_mutex_lock(&info->fork[philo->right]);
	prints(info, get_time() - info->t_start, philo->id, FORK);
	prints(info, get_time() - info->t_start, philo->id, EAT);
	philo->t_last_eat = get_time();
	philo->n_eat += 1;
	psleep(info->t_eat);
	pthread_mutex_unlock(&(info->fork[philo->right]));
	pthread_mutex_unlock(&(info->fork[philo->left]));
	return (0);
}

void	*philo_act(void *philo)
{
	t_philo	*tmp_philo;
	t_info	*tmp_info;
	int		dead;

	tmp_philo = philo;
	tmp_info = tmp_philo->info;
	if (tmp_philo->id % 2 == 1) // 홀수는 기다려?
		usleep(100);
	dead = 0;
	while (1) // 반복!
	{
		//죽었는지 확인
		pthread_mutex_lock(&(tmp_info->check_death));
		dead = tmp_info->is_dead; // 읽기만 하는데도 mutex? (다른 애는 쓰고 있을 수 있기 때문에..)
		pthread_mutex_unlock(&(tmp_info->check_death));
		if (dead)
			break ;

		// 정해진 횟수만큼 먹었는지 확인
		if (tmp_philo->n_eat == tmp_philo->info->n_must_eat)
			break ;

		if (philo_eat(tmp_info, tmp_philo))
			break ;
		prints(tmp_info, get_time() - tmp_info->t_start, tmp_philo->id, SLEEP); // 잘거임
		psleep(tmp_info->t_sleep);
		prints(tmp_info, get_time() - tmp_info->t_start, tmp_philo->id, THINK); // 생각할거임
	}
	return (0);
}

int	philo_start(t_info *info, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < info->n_philo)
	{
		philo[i].t_last_eat = get_time();
		if (pthread_create(&philo[i].thread, 0, philo_act, &philo[i]))
			return (1);
	}
	i = -1;
	while (++i < info->n_philo)
		pthread_join(philo[i].thread, 0); //join하는 이유?
	i = -1;
	while (++i < info->n_philo)
		pthread_mutex_destroy(&(info->fork[i])); // 포크 정리
	pthread_mutex_destroy(&(info->print)); // print mutex 정리
	// check_death 정리는 ?
	free(info->fork);
	free(philo);
	return (0);
}
