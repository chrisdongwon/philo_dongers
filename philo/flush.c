/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flush.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 00:01:55 by cwon              #+#    #+#             */
/*   Updated: 2025/04/27 21:44:16 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	error(const char *fn_name, const char *context)
{
	printf("Error %d: %s (from %s) failed\n", errno, fn_name, context);
	return (false);
}

bool	flush_mutex(t_table *table, int n, bool result)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (!safe_mutex_destroy(&table->fork[i++], "flush_mutex"))
			result = false;
	}
	result = safe_mutex_destroy(&table->mealcount_lock, "flush_mutex") && \
			result;
	result = safe_mutex_destroy(&table->print_lock, "flush_mutex") && result;
	return (safe_mutex_destroy(&table->stop_lock, "flush_mutex") && result);
}

bool	flush_philo(t_table *table, int n, bool result)
{
	int		i;
	t_philo	*philo;

	i = 0;
	while (i < n)
	{
		philo = &table->philo[i++];
		if (!safe_mutex_destroy(&philo->lastmeal_lock, "flush_philo"))
			result = false;
	}
	return (result);
}

int	flush(t_table *table, bool mutex, int exit_status)
{
	if (mutex)
	{
		if (!flush_mutex(table, table->size, true))
			exit_status = EXIT_FAILURE;
		if (!flush_philo(table, table->size, true))
			exit_status = EXIT_FAILURE;
	}
	free(table->fork);
	free(table->philo);
	if (errno)
		return (EXIT_FAILURE);
	return (exit_status);
}
