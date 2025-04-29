/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphore_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 21:17:19 by cwon              #+#    #+#             */
/*   Updated: 2025/04/29 13:35:45 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

bool	safe_sem_close(sem_t *sem, const char *context)
{
	if (sem_close(sem) == -1)
		return (error("sem_close", context));
	return (true);
}

bool	safe_sem_post(sem_t *sem, const char *context)
{
	if (sem_post(sem) == -1)
		return (error("sem_post", context));
	return (true);
}

bool	safe_sem_unlink(const char *sem_name, const char *context)
{
	if (sem_unlink(sem_name) == -1)
		return (error("sem_unlink", context));
	return (true);
}

bool	safe_sem_wait(sem_t	*sem, const char *context)
{
	if (sem_wait(sem) == -1)
		return (error("sem_wait", context));
	return (true);
}
