/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flush_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 22:18:09 by cwon              #+#    #+#             */
/*   Updated: 2025/04/22 22:50:06 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

bool	error(const char *str)
{
	printf("errno: %d\n", errno);
	printf("error: %s failed\n", str);
	return (false);
}

int	flush(t_table *table, bool flush_sem, int exit_status)
{
	bool	close;
	bool	unlink;

	free(table->philo);
	if (flush_sem)
	{
		close = safe_sem_close(table->death);
		close = safe_sem_close(table->forks) && close;
		unlink = safe_sem_unlink(DEATH_SEM);
		unlink = safe_sem_unlink(FORKS_SEM) && unlink;
		if (!close || !unlink)
			return (EXIT_FAILURE);
	}
	return (exit_status);
}
