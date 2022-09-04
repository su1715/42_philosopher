/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujpark <sujpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 15:59:19 by sujpark           #+#    #+#             */
/*   Updated: 2022/09/04 16:41:50 by sujpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_str_error(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(ft_isdigit(str[i])))
			if (!(i == 0 && str[i] == '+'))
				return (1);
		++i;
	}
	return (0);
}

void	check_parse_error(char *argv[])
{
	int	i;

	i = 0;
	while (argv[++i] != NULL)
	{
		if (check_str_error(argv[i]))
			error_exit("argv str error");
	}
}

long int	parse_atoi(const char *str) // long int ?
{
	long int	temp;

	temp = 0;
	if (*str == '+')
		str++;
	while (*str)
	{
		temp = (temp * 10) + (*str - '0');
		if (temp > INT32_MAX)
			error_exit("parse_atoi error");
		str++;
	}
	return (temp);
}

t_arguments	*set_arguments(int argc, char *argv[])
{
	t_arguments	*args;

	args = ft_calloc(1, sizeof(t_arguments));
	args->n_of_philo = parse_atoi(argv[1]);
	args->time_to_die = parse_atoi(argv[2]);
	args->time_to_eat = parse_atoi(argv[3]);
	args->time_to_sleep = parse_atoi(argv[4]);
	if (argc == 6)
		args->n_of_must_eat = parse_atoi(argv[5]);
	else
		args->n_of_must_eat = -1;
	return (args);
}

t_arguments	*parse(int argc, char *argv[])
{
	t_arguments	*args;

	if (!(argc == 5 || argc == 6))
		error_exit("argc error");
	check_parse_error(argv);
	args = set_arguments(argc, argv);
	return (args);
}
