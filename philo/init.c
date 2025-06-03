/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 23:11:51 by cwon              #+#    #+#             */
/*   Updated: 2025/06/03 16:30:04 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// static void	choose_forks(t_philo *philo)
// {
// 	t_mutex	*temp;
// 	t_table	*table;

// 	table = philo->table;
// 	philo->fork1 = &table->fork[(philo->id - 1) % table->size];
// 	philo->fork2 = &table->fork[(philo->id) % table->size];

// 	if (philo->id % 2 == 0)
// 	{
// 		temp = philo->fork1;
// 		philo->fork1 = philo->fork2;
// 		philo->fork2 = temp;
// 	}
// }

static void	choose_forks(t_philo *philo)
{
	int		i;
	int		j;
	int		temp;
	t_table	*table;

	table = philo->table;
	i = (philo->id - 1) % table->size;
	j = (philo->id) % table->size;
	if (j < i)
	{
		temp = i;
		i = j;
		j = temp;
	}
	philo->fork1 = &table->fork[i];
	philo->fork2 = &table->fork[j];
}

bool	init_mutex(t_table *table)
{
	int	i;

	if (!safe_mutex_init(&table->mealcount_lock, "init_mutex"))
		return (false);
	if (!safe_mutex_init(&table->print_lock, "init_mutex"))
	{
		safe_mutex_destroy(&table->mealcount_lock, "init_mutex");
		return (false);
	}
	if (!safe_mutex_init(&table->stop_lock, "init_mutex"))
	{
		safe_mutex_destroy(&table->mealcount_lock, "init_mutex");
		safe_mutex_destroy(&table->print_lock, "init_mutex");
		return (false);
	}
	i = -1;
	while (++i < table->size)
	{
		if (!safe_mutex_init(&table->fork[i], "init_mutex"))
			return (flush_mutex(table, i, false));
	}
	return (true);
}

bool	init_philo(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while (++i < table->size)
	{
		philo = &table->philo[i];
		philo->id = i + 1;
		philo->mealcount = 0;
		philo->table = table;
		choose_forks(philo);
		if (!get_timestamp(&philo->lastmeal) || \
!safe_mutex_init(&philo->lastmeal_lock, "init_philo"))
			return (flush_philo(table, i, false));
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
	table->stop = false;
	table->philo = 0;
	table->fork = 0;
	table->philo = (t_philo *)malloc(table->size * sizeof(t_philo));
	if (!table->philo)
		return (error("malloc", "init_table"));
	table->fork = (t_mutex *)malloc(table->size * sizeof(t_mutex));
	if (!table->fork)
		return (error("malloc", "init_table"));
	return (true);
}
