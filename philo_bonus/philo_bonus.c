/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 20:59:37 by cwon              #+#    #+#             */
/*   Updated: 2025/04/29 16:41:47 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static bool	launch_philo(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->size)
	{
		table->philo[i].pid = fork();
		if (table->philo[i].pid == -1)
		{
			kill_processes(table, i, false);
			return (error("fork", "launch_philo"));
		}
		if (!table->philo[i].pid)
			philo_routine(&table->philo[i]);
	}
	i = -1;
	while (++i < table->size)
	{
		if (!safe_sem_wait(table->quit, "launch_philo"))
			kill_processes(table, i, false);
	}
	return (kill_processes(table, table->size, true));
}

int	philosophers(int argc, char **argv)
{
	t_table	table;

	if (!init_table(&table, argc, argv) || !init_sem(&table))
		return (flush(&table, false, EXIT_FAILURE));
	if (!init_philo(&table) || !launch_philo(&table))
		return (flush(&table, true, EXIT_FAILURE));
	return (flush(&table, true, EXIT_SUCCESS));
}
