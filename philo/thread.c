/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 14:18:46 by cwon              #+#    #+#             */
/*   Updated: 2025/04/27 19:02:14 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	safe_thread_create(pthread_t *thread, t_routine routine, void *arg, \
							const char *context)
{
	errno = pthread_create(thread, 0, routine, arg);
	if (errno)
		return (error("pthread_create", context));
	return (true);
}

bool	safe_thread_join(pthread_t thread, const char *context)
{
	errno = pthread_join(thread, 0);
	if (errno)
		return (error("pthread_join", context));
	return (true);
}
