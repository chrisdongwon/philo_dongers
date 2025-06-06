/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 23:43:49 by cwon              #+#    #+#             */
/*   Updated: 2025/04/27 00:00:54 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	safe_mutex_destroy(t_mutex *mutex, const char *context)
{
	errno = pthread_mutex_destroy(mutex);
	if (errno)
		return (error("pthread_mutex_destroy", context));
	return (true);
}

bool	safe_mutex_init(t_mutex *mutex, const char *context)
{
	errno = pthread_mutex_init(mutex, 0);
	if (errno)
		return (error("pthread_mutex_init", context));
	return (true);
}

bool	safe_mutex_lock(t_mutex *mutex, const char *context)
{
	errno = pthread_mutex_lock(mutex);
	if (errno)
		return (error("pthread_mutex_lock", context));
	return (true);
}

bool	safe_mutex_unlock(t_mutex *mutex, const char *context)
{
	errno = pthread_mutex_unlock(mutex);
	if (errno)
		return (error("pthread_mutex_unlock", context));
	return (true);
}
