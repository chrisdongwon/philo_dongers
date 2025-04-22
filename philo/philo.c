/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:29:48 by cwon              #+#    #+#             */
/*   Updated: 2025/04/22 23:07:06 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	join_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->size)
	{
		if (!safe_thread_join(table->philo[i++].thread, "join_threads"))
			return (false);
	}
	return (safe_thread_join(table->watchdog, "join_threads"));
}

static int	flush(t_table *table, bool flush_mutex, int exit_status)
{
	int	i;

	if (flush_mutex)
	{
		i = 0;
		while (i < table->size)
			safe_mutex_destroy(&table->fork[i++], "flush");
		safe_mutex_destroy(&table->lastmeal_lock, "flush");
		safe_mutex_destroy(&table->mealcount_lock, "flush");
		safe_mutex_destroy(&table->stop_lock, "flush");
	}
	free(table->fork);
	free(table->philo);
	return (exit_status);
}

bool	error(const char *fn_name, const char *context)
{
	printf("errno: %d\n", errno);
	printf("error: %s (from %s) failed\n", fn_name, context);
	return (false);
}

int	philosophers(int argc, char **argv)
{
	t_table	table;

	if (!init_param(argc, argv, &table) || !init_mutex(&table))
		return (flush(&table, false, EXIT_FAILURE));
	if (!init_philo(&table) || !join_threads(&table))
		return (flush(&table, true, EXIT_FAILURE));
	return (flush(&table, true, EXIT_SUCCESS));
}
