/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 21:00:41 by cwon              #+#    #+#             */
/*   Updated: 2025/04/29 15:55:13 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

bool	init_philo(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while (++i < table->size)
	{
		philo = &table->philo[i];
		philo->alive = true;
		philo->min_reached = false;
		philo->id = i + 1;
		philo->mealcount = 0;
		philo->table = table;
		if (!get_timestamp(&philo->lastmeal))
			return (false);
	}
	return (true);
}

bool	init_sem(t_table *table)
{
	sem_unlink(FORKS_SEM);
	sem_unlink(LOCK_SEM);
	sem_unlink(QUIT_SEM);
	errno = 0;
	table->forks = sem_open(FORKS_SEM, O_CREAT | O_EXCL, 0644, table->size);
	if (table->forks == SEM_FAILED)
		return (error("sem_open", "init_sem"));
	table->lock = sem_open(LOCK_SEM, O_CREAT | O_EXCL, 0644, 1);
	if (table->lock == SEM_FAILED)
	{
		safe_sem_close(table->forks, "init_sem");
		safe_sem_unlink(FORKS_SEM, "init_sem");
		return (error("sem_open", "init_sem"));
	}
	table->quit = sem_open(QUIT_SEM, O_CREAT | O_EXCL, 0644, 0);
	if (table->quit == SEM_FAILED)
	{
		safe_sem_close(table->forks, "init_sem");
		safe_sem_close(table->lock, "init_sem");
		safe_sem_unlink(FORKS_SEM, "init_sem");
		safe_sem_unlink(LOCK_SEM, "init_sem");
		return (error("sem_open", "init_sem"));
	}
	return (true);
}

bool	init_table(t_table *table, int argc, char **argv)
{
	table->size = ascii_to_nonneg_int(argv[1]);
	table->death_time = ascii_to_nonneg_int(argv[2]);
	table->eat_time = ascii_to_nonneg_int(argv[3]);
	table->sleep_time = ascii_to_nonneg_int(argv[4]);
	table->min_meals = -1;
	if (argc == 6)
		table->min_meals = ascii_to_nonneg_int(argv[5]);
	table->philo = (t_philo *)malloc(table->size * sizeof(t_philo));
	if (!table->philo)
		return (error("malloc", "init_table"));
	return (true);
}
