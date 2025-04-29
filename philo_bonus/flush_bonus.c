/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flush_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 20:59:25 by cwon              #+#    #+#             */
/*   Updated: 2025/04/29 16:44:37 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static bool	flush_sem(t_table *table)
{
	bool	result;

	result = safe_sem_close(table->forks, "flush_sem");
	result = safe_sem_close(table->lock, "flush_sem") && result;
	result = safe_sem_close(table->quit, "flush_sem") && result;
	result = (sem_unlink(FORKS_SEM) != -1) && result;
	result = (sem_unlink(LOCK_SEM) != -1) && result;
	return ((sem_unlink(QUIT_SEM) != -1) && result);
}

bool	error(const char *fn_name, const char *context)
{
	printf("Error %d: %s (from %s) failed\n", errno, fn_name, context);
	return (false);
}

int	flush_routine(t_table *table, int exit_status)
{
	if (!safe_sem_close(table->forks, "flush_routine"))
		exit_status = EXIT_FAILURE;
	if (!safe_sem_close(table->lock, "flush_routine"))
		exit_status = EXIT_FAILURE;
	if (!safe_sem_close(table->quit, "flush_routine"))
		exit_status = EXIT_FAILURE;
	free(table->philo);
	if (errno)
		return (EXIT_FAILURE);
	return (exit_status);
}

int	flush(t_table *table, bool sem, int exit_status)
{
	if (sem && !flush_sem(table))
		exit_status = EXIT_FAILURE;
	free(table->philo);
	if (errno)
		return (EXIT_FAILURE);
	return (exit_status);
}
