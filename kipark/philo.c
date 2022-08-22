/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujpark <sujpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 14:56:55 by baggiseon         #+#    #+#             */
/*   Updated: 2022/08/22 15:31:20 by sujpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	int	*get_parse;

	if (argc != 5 && argc != 6)
		return (print_error(1));
	get_parse = parse(argc - 1, ++argv);
	if (get_parse == NULL)
		return (print_error(1));
	run_thread(get_parse);
}
