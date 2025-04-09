/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watchdog.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 09:19:59 by cwon              #+#    #+#             */
/*   Updated: 2025/04/09 12:25:17 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	get_elapsed(t_table *table, int i, long *elapsed)
{
	t_time	now;

	if (!safe_gettimeofday(&now) || !safe_mutex_lock(&table->lock))
		return (false);
	*elapsed = time_diff_ms(&table->philo[i].last_meal, &now);
	return (safe_mutex_unlock(&table->lock));
}

static void	*philo_death(t_table *table, int i)
{
	t_llong	timestamp;

	if (!get_timestamp_ms(&timestamp, 0))
		return (0);
	printf("%lld %d has died\n", timestamp, i + 1);
	if (!safe_mutex_lock(&table->lock))
		return (0);
	table->stop = 1;
	safe_mutex_unlock(&table->lock);
	return (0);
}

void	*watchdog_routine(void *arg)
{
	int		i;
	bool	quit;
	long	elapsed;
	t_table	*table;

	table = (t_table *)arg;
	i = 0;
	quit = false;
	while (!quit)
	{
		if (!safe_mutex_lock(&table->lock))
			return (0);
		quit = table->stop;
		if (!safe_mutex_unlock(&table->lock) || quit || \
			!get_elapsed(table, i, &elapsed))
			return (0);
		if (elapsed > table->death_time)
			return (philo_death(table, i));
		i = (i + 1) % table->size;
	}
	return (0);
}
