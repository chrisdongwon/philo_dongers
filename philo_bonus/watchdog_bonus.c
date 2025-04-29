/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watchdog_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:26:17 by cwon              #+#    #+#             */
/*   Updated: 2025/04/29 16:05:15 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	end_watchdog(t_table *table, int exit_status)
{
	int	i;

	i = -1;
	while (++i < table->size)
	{
		if (!safe_sem_post(table->quit, "end_watchdog"))
			exit_status = EXIT_FAILURE;
	}
	exit(flush_routine(table, exit_status));
}

static void	detect_starvation(t_philo *philo, t_table *table)
{
	t_time	timestamp;

	if (!get_timestamp(&timestamp))
	{
		safe_sem_post(table->lock, "watchdog_routine");
		end_watchdog(table, EXIT_FAILURE);
	}
	if (philo->alive && \
		((int)(timestamp - philo->lastmeal) > table->death_time))
	{
		philo->alive = false;
		printf("%" PRIu64 " %d has died\n", timestamp, philo->id);
		if (!safe_sem_post(table->lock, "watchdog_routine"))
			end_watchdog(table, EXIT_FAILURE);
		end_watchdog(table, EXIT_SUCCESS);
	}
}

void	*watchdog_routine(void *arg)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)arg;
	table = philo->table;
	while (true)
	{
		if (!safe_sem_wait(table->lock, "watchdog_routine"))
			end_watchdog(table, EXIT_FAILURE);
		detect_starvation(philo, table);
		if (!safe_sem_post(table->lock, "watchdog_routine") || \
			!safe_usleep(500, "watchdog_routine"))
			end_watchdog(table, EXIT_FAILURE);
	}
	return (0);
}
