/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 22:14:07 by cwon              #+#    #+#             */
/*   Updated: 2025/04/25 22:35:08 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	if (valid_args(argc, argv))
		return (philosophers(argc, argv));
	else
	{
		printf("usage: %s <number_of_philosophers> <time_to_die> \
<time_to_eat> <time_to_sleep> [number_of_times_philosophers_must_eat]\n", \
argv[0]);
		return (EXIT_FAILURE);
	}
}
