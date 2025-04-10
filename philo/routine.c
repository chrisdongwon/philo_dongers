/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 14:43:05 by cwon              #+#    #+#             */
/*   Updated: 2025/04/10 14:05:06 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	philo_eat(t_philo *philo)
{
	bool	quit;
	t_llong	timestamp;
	t_table	*table;

	table = philo->table;
	if (!safe_mutex_lock(&table->lock))
	{
		release_forks(philo);
		return (false);
	}
	quit = table->stop;
	if (!safe_mutex_unlock(&table->lock) || quit || \
		!get_timestamp_ms(&timestamp, philo))
	{
		release_forks(philo);
		return (false);
	}
	printf("%lld %d is eating\n", timestamp, philo->id + 1);
	if (!safe_usleep(table->eat_time) || !release_forks(philo))
		return (false);
	if (table->min_meals)
	{
		if (!update_mealcount(philo))
			return (false);
	}
	return (true);
}

static bool	philo_forks(t_philo *philo)
{
	int		first;
	int		second;

	choose_forks(philo, &first, &second);
	if (first == second)
	{
		grab_fork(philo, first);
		safe_mutex_unlock(&philo->table->fork[first]);
		return (false);
	}
	if (!grab_fork(philo, first))
		return (false);
	if (!grab_fork (philo, second))
	{
		safe_mutex_unlock(&philo->table->fork[first]);
		return (false);
	}
	return (true);
}

static bool	philo_sleep(t_philo *philo)
{
	bool	quit;
	t_llong	timestamp;
	t_table	*table;

	table = philo->table;
	if (!safe_mutex_lock(&table->lock))
		return (false);
	quit = table->stop;
	if (!safe_mutex_unlock(&table->lock) || quit || \
		!get_timestamp_ms(&timestamp, 0))
		return (false);
	printf("%lld %d is sleeping\n", timestamp, philo->id + 1);
	return (safe_usleep(table->sleep_time));
}

static bool	philo_think(t_philo *philo)
{
	bool	quit;
	t_llong	timestamp;
	t_table	*table;

	table = philo->table;
	if (!safe_mutex_lock(&table->lock))
		return (false);
	quit = table->stop;
	if (!safe_mutex_unlock(&table->lock) || quit || \
		!get_timestamp_ms(&timestamp, 0))
		return (false);
	printf("%lld %d is thinking\n", timestamp, philo->id + 1);
	return (true);
}

// it looks like "quit" flag needs to be checked IMMEDIATELY before the 
// status is printed
void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo_think(philo) && philo_forks(philo) && philo_eat(philo) \
			&& philo_sleep(philo))
		continue ;
	return (0);
}
