/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 22:34:00 by cwon              #+#    #+#             */
/*   Updated: 2025/06/03 16:28:16 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	join_threads(t_table *table, int n, bool result)
{
	int	i;

	i = -1;
	while (++i < n)
	{
		if (!safe_thread_join(table->philo[i].thread, "join_threads"))
			result = false;
	}
	return (result);
}

static bool	launch_philo(t_table *table)
{
	int	i;

	if (!safe_thread_create(&table->watchdog, watchdog_routine, table, \
"launch_philo"))
		return (false);
	i = -1;
	while (++i < table->size)
	{
		if (!safe_thread_create(&table->philo[i].thread, philo_routine, \
&table->philo[i], "launch_philo"))
		{
			join_threads(table, i, false);
			safe_thread_join(table->watchdog, "launch_philo");
			return (false);
		}
	}
	if (!join_threads(table, table->size, true))
	{
		safe_thread_join(table->watchdog, "launch_philo");
		return (false);
	}
	return (safe_thread_join(table->watchdog, "launch_philo"));
}

int	philosophers(int argc, char **argv)
{
	t_table	table;

	if (!init_table(&table, argc, argv) || !init_mutex(&table))
		return (flush(&table, false, EXIT_FAILURE));
	if (!init_philo(&table) || !launch_philo(&table))
		return (flush(&table, true, EXIT_FAILURE));
	return (flush(&table, true, EXIT_SUCCESS));
}
