/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 14:18:46 by cwon              #+#    #+#             */
/*   Updated: 2025/04/29 13:21:34 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

bool	safe_thread_create(pthread_t *thread, t_routine routine, void *arg, \
							const char *context)
{
	errno = pthread_create(thread, 0, routine, arg);
	if (errno)
		return (error("pthread_create", context));
	return (true);
}

bool	safe_thread_detach(pthread_t thread, const char *context)
{
	errno = pthread_detach(thread);
	if (errno)
		return (error("pthread_detach", context));
	return (true);
}
