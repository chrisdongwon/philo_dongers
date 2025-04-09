/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:33:14 by cwon              #+#    #+#             */
/*   Updated: 2025/04/02 11:08:14 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	get_timestamp_ms(t_llong *timestamp, t_philo *philo)
{
	t_table	*table;
	t_time	tv;

	if (!safe_gettimeofday(&tv))
		return (false);
	if (philo)
	{
		table = philo->table;
		if (!safe_mutex_lock(&table->lock))
			return (false);
		philo->last_meal = tv;
		if (!safe_mutex_unlock(&table->lock))
			return (false);
	}
	*timestamp = (tv.tv_sec * 1000LL) + (tv.tv_usec / 1000);
	return (true);
}

bool	safe_gettimeofday(t_time *tv)
{
	if (gettimeofday(tv, 0))
		return (error("gettimeofday"));
	return (true);
}

bool	safe_usleep(int msec)
{
	if (usleep((unsigned int)msec * 1000))
		return (error("usleep"));
	return (true);
}

long	time_diff_ms(t_time *start, t_time *end)
{
	return ((end->tv_sec - start->tv_sec) * 1000 + \
			(end->tv_usec - start->tv_usec) / 1000);
}
