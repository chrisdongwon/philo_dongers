/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 20:52:13 by cwon              #+#    #+#             */
/*   Updated: 2025/04/27 20:52:17 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
