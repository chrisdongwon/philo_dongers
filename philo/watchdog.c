/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watchdog.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 09:19:59 by cwon              #+#    #+#             */
/*   Updated: 2025/04/22 23:05:29 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	get_elapsed(t_table *table, int i, long *elapsed)
{
	t_time	now;

	if (!safe_mutex_lock(&table->lastmeal_lock, "get_elapseed"))
		return (false);
	if (!safe_gettimeofday(&now, "get_elapseed"))
	{
		safe_mutex_unlock(&table->lastmeal_lock, "get_elapseed");
		return (false);
	}
	*elapsed = time_diff(&table->philo[i].lastmeal, &now);
	return (safe_mutex_unlock(&table->lastmeal_lock, "get_elapseed"));
}

void	*terminate(t_table *table, int i, bool is_dead)
{
	t_llong	timestamp;

	if (!safe_mutex_lock(&table->stop_lock, "terminate"))
		return (0);
	table->stop = 1;
	if (!safe_mutex_unlock(&table->stop_lock, "terminate") || \
		!get_timestamp(&timestamp, 0))
		return (0);
	if (is_dead)
		printf("%lld %d has died\n", timestamp, i + 1);
	return (0);
}

void	*watchdog_routine(void *arg)
{
	int		i;
	long	elapsed;
	t_table	*table;

	table = (t_table *)arg;
	i = 0;
	while (true)
	{
		if (!safe_mutex_lock(&table->stop_lock, "watchdog_routine"))
			return (0);
		if (table->stop)
		{
			safe_mutex_unlock(&table->stop_lock, "watchdog_routine");
			return (0);
		}
		safe_mutex_unlock(&table->stop_lock, "watchdog_routine");
		if (!safe_usleep(1, "watchdog_routine") || \
			!get_elapsed(table, i, &elapsed))
			return (terminate(table, i, false));
		if (elapsed > table->death_time)
			return (terminate(table, i, true));
		i = (i + 1) % table->size;
	}
	return (0);
}
