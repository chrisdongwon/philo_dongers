/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 11:04:58 by cwon              #+#    #+#             */
/*   Updated: 2025/03/27 11:07:12 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	safe_mutex_destroy(t_mutex *mutex)
{
	errno = pthread_mutex_destroy(mutex);
	if (errno)
		return (error("pthread_mutex_destroy"));
	return (true);
}

bool	safe_mutex_init(t_mutex *mutex)
{
	errno = pthread_mutex_init(mutex, 0);
	if (errno)
		return (error("pthread_mutex_init"));
	return (true);
}

bool	safe_mutex_lock(t_mutex *mutex)
{
	errno = pthread_mutex_lock(mutex);
	if (errno)
		return (error("pthread_mutex_lock"));
	return (true);
}

bool	safe_mutex_unlock(t_mutex *mutex)
{
	errno = pthread_mutex_unlock(mutex);
	if (errno)
		return (error("pthread_mutex_unlock"));
	return (true);
}
