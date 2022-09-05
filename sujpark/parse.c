/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujpark <sujpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 15:59:19 by sujpark           #+#    #+#             */
/*   Updated: 2022/09/05 22:31:40 by sujpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_str_error(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (!(ft_isdigit(str[i])))
			if (!(i == 0 && str[i] == '+'))
				return (1);
	}
	return (0);
}

int	check_parse_error(char *argv[])
{
	int	i;

	i = 0;
	while (argv[++i] != NULL)
	{
		if (check_str_error(argv[i]))
			return (1);
	}
	return (0);
}

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

t_arguments	*set_arguments(int argc, char *argv[])
{
	t_arguments	*args;

	args = malloc(sizeof(t_arguments));
	if (!args)
	{
		print_error("malloc args error");
		return (NULL);
	}
	args->n_of_philo = parse_atoi(argv[1]);
	args->time_to_die = parse_atoi(argv[2]);
	args->time_to_eat = parse_atoi(argv[3]);
	args->time_to_sleep = parse_atoi(argv[4]);
	if (argc == 6)
		args->n_of_must_eat = parse_atoi(argv[5]);
	else
		args->n_of_must_eat = -1;
	if (check_args_too_big(args))
	{
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
