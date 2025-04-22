/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 21:42:29 by cwon              #+#    #+#             */
/*   Updated: 2025/04/22 22:46:39 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

bool	init_sem(t_table *table)
{
	sem_unlink(DEATH_SEM);
	sem_unlink(FORKS_SEM);
	table->death = safe_sem_open(DEATH_SEM, 1);
	table->forks = safe_sem_open(FORKS_SEM, table->size);
	if (table->death == SEM_FAILED || table->forks == SEM_FAILED)
	{
		if (table->death != SEM_FAILED)
			sem_close_and_unlink(table->death, DEATH_SEM);
		if (table->forks != SEM_FAILED)
			sem_close_and_unlink(table->forks, FORKS_SEM);
		return (false);
	}
	return (true);
}

// is it necessary for philo to be initialized to zeroes?
bool	init_table(int argc, char **argv, t_table *table)
{
	table->size = ascii_to_nonneg_int(argv[1]);
	table->death_time = ascii_to_nonneg_int(argv[2]);
	table->eat_time = ascii_to_nonneg_int(argv[3]);
	table->sleep_time = ascii_to_nonneg_int(argv[4]);
	table->min_meals = 0;
	if (argc == 6)
		table->min_meals = ascii_to_nonneg_int(argv[5]);
	table->philo = (pid_t *)malloc(table->size * sizeof(pid_t));
	return (table->philo);
}
