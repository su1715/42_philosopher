/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujpark <sujpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 15:59:19 by sujpark           #+#    #+#             */
/*   Updated: 2022/09/06 18:43:34 by sujpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	parse_atoi(const char *str)
{
	long long	temp;

	temp = 0;
	if (*str == '+')
		str++;
	while (*str)
	{
		temp = (temp * 10) + (*str - '0');
		if (temp > INT32_MAX)
		{
			print_error("parse_atoi error");
			temp = TOO_BIG;
			return (temp);
		}
		str++;
	}
	return (temp);
}

int	args_atoi(int argc, char *argv[], t_arguments *args)
{
	args->n_of_philo = parse_atoi(argv[1]);
	if (args->n_of_philo == 0)
		return (1);
	args->time_to_die = parse_atoi(argv[2]);
	args->time_to_eat = parse_atoi(argv[3]);
	args->time_to_sleep = parse_atoi(argv[4]);
	if (argc == 6)
		args->n_of_must_eat = parse_atoi(argv[5]);
	else
		args->n_of_must_eat = -1;
	return (0);
}

t_arguments	*set_arguments(int argc, char *argv[])
{
	t_arguments	*args;

	args = malloc(sizeof(t_arguments));
	if (!args)
	{
		print_error("malloc args error");
		return (NULL);
	}
	if (args_atoi(argc, argv, args) || check_args_too_big(args))
	{
		print_error("args atoi error");
		free(args);
		return (NULL);
	}
	return (args);
}

t_arguments	*parse(int argc, char *argv[])
{
	t_arguments	*args;

	if (!(argc == 5 || argc == 6))
	{
		print_error("argc error");
		return (NULL);
	}
	if (check_parse_error(argv))
	{
		print_error("argv str error");
		return (NULL);
	}
	args = set_arguments(argc, argv);
	return (args);
}
