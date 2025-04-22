/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:19:31 by cwon              #+#    #+#             */
/*   Updated: 2025/04/22 22:44:58 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	philosophers(int argc, char **argv)
{
	t_table	table;

	if (!init_table(argc, argv, &table))
		return (EXIT_FAILURE);
	if (!init_sem(&table))
		return (flush(&table, false, EXIT_FAILURE));
	printf("good so far\n");
	return (flush(&table, true, EXIT_SUCCESS));
}
