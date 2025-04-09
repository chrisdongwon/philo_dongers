/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:45:27 by cwon              #+#    #+#             */
/*   Updated: 2025/04/09 11:49:36 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	argv_to_table(int argc, char **argv, t_table *table)
{
	table->size = ascii_to_nonneg_int(argv[1]);
	table->death_time = ascii_to_nonneg_int(argv[2]);
	table->eat_time = ascii_to_nonneg_int(argv[3]);
	table->sleep_time = ascii_to_nonneg_int(argv[4]);
	table->min_meals = 0;
	if (argc == 6)
		table->min_meals = ascii_to_nonneg_int(argv[5]);
}

bool	init_mutex(t_table *table)
{
	int	i;

	if (!safe_mutex_init(&table->lock))
		return (false);
	if (!safe_mutex_init(&table->mealcount_lock))
	{
		safe_mutex_destroy(&table->lock);
		return (false);
	}
	i = 0;
	while (i < table->size)
	{
		if (!safe_mutex_init(&table->fork[i]))
		{
			while (--i >= 0)
				safe_mutex_destroy(&table->fork[i]);
			safe_mutex_destroy(&table->lock);
			safe_mutex_destroy(&table->mealcount_lock);
			return (false);
		}
		i++;
	}
	return (true);
}

bool	init_param(int argc, char **argv, t_table *table)
{
	argv_to_table(argc, argv, table);
	table->min_reached = 0;
	table->stop = false;
	table->fork = (t_mutex *)malloc(table->size * sizeof(t_mutex));
	table->philo = (t_philo *)malloc(table->size * sizeof(t_philo));
	if (!table->fork || !table->philo)
		return (error("malloc"));
	return (true);
}

bool	init_philo(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->size)
	{
		table->philo[i].id = i;
		table->philo[i].meal_count = 0;
		table->philo[i].table = table;
		if (!safe_gettimeofday(&table->philo[i].last_meal) || \
			!safe_thread_create(&table->philo[i].thread, philo_routine, \
			&table->philo[i]))
			return (false);
		i++;
	}
	return (safe_thread_create(&table->watchdog, watchdog_routine, table));
}
