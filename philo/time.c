/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:33:14 by cwon              #+#    #+#             */
/*   Updated: 2025/04/22 23:28:41 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	get_timestamp(t_llong *timestamp, t_philo *philo)
{
	t_table	*table;
	t_time	tv;

	if (philo)
	{
		table = philo->table;
		if (!safe_mutex_lock(&table->lastmeal_lock, "get_timestamp"))
			return (false);
		if (!safe_gettimeofday(&philo->lastmeal, "get_timestamp"))
		{
			safe_mutex_unlock(&table->lastmeal_lock, "get_timestamp");
			return (false);
		}
		*timestamp = (philo->lastmeal.tv_sec * 1000LL) + \
					(philo->lastmeal.tv_usec / 1000);
		if (!safe_mutex_unlock(&table->lastmeal_lock, "get_timestamp"))
			return (false);
	}
	else
	{
		if (!safe_gettimeofday(&tv, "get_timestamp"))
			return (false);
		*timestamp = (tv.tv_sec * 1000LL) + (tv.tv_usec / 1000);
	}
	return (true);
}

bool	safe_gettimeofday(t_time *tv, const char *context)
{
	if (gettimeofday(tv, 0))
		return (error("gettimeofday", context));
	return (true);
}

bool	safe_usleep(int ms, const char *context)
{
	if (usleep(ms * 1000))
		return (error("usleep", context));
	return (true);
}

long	time_diff(t_time *start, t_time *end)
{
	long	sec_diff;
	long	usec_diff;

	sec_diff = (end->tv_sec - start->tv_sec) * 1000;
	usec_diff = (end->tv_usec - start->tv_usec) / 1000;
	return (sec_diff + usec_diff);
}
