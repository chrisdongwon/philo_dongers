/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphore_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:57:03 by cwon              #+#    #+#             */
/*   Updated: 2025/04/22 22:37:55 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

bool	safe_sem_close(sem_t *sem)
{
	if (sem_close(sem))
		return (error("sem_close"));
	return (true);
}

bool	safe_sem_unlink(const char *name)
{
	if (sem_unlink(name))
		return (error("sem_unlink"));
	return (true);
}

sem_t	*safe_sem_open(const char *name, unsigned int value)
{
	sem_t	*result;

	result = sem_open(name, O_CREAT | O_EXCL, 0644, value);
	if (result == SEM_FAILED)
		error("sem_open");
	return (result);
}

void	sem_close_and_unlink(sem_t *sem, const char *sem_name)
{
	safe_sem_close(sem);
	safe_sem_unlink(sem_name);
}
