/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 02:00:37 by cwon              #+#    #+#             */
/*   Updated: 2025/06/03 16:40:29 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	get_timestamp(t_time *timestamp)
{
	t_timeval	tv;

	if (gettimeofday(&tv, 0))
		return (error("gettimeofday", "get_timestamp"));
	*timestamp = (t_time)(tv.tv_sec) * 1000 + (t_time)(tv.tv_usec) / 1000;
	return (true);
}

bool	print_log(t_philo *philo, const char *str)
{
	bool	result;
	t_time	timestamp;

	if (!safe_mutex_lock(&philo->table->stop_lock, "print_log"))
		return (false);
	if (!safe_mutex_lock(&philo->table->print_lock, "print_log"))
	{
		safe_mutex_unlock(&philo->table->stop_lock, "print_log");
		return (false);
	}
	if (!philo->table->stop)
	{
		if (!get_timestamp(&timestamp) || \
(printf("%" PRIu64 " %d %s\n", timestamp, philo->id, str) <= 0))
		{
			safe_mutex_unlock(&philo->table->stop_lock, "print_log");
			safe_mutex_unlock(&philo->table->print_lock, "print_log");
			return (false);
		}
	}
	result = safe_mutex_unlock(&philo->table->stop_lock, "print_log");
	return (safe_mutex_unlock(&philo->table->print_lock, "print_log") && \
result);
}

bool	quit_now(t_table *table)
{
	bool	result;

	result = false;
	if (!safe_mutex_lock(&table->stop_lock, "quit_now"))
		return (true);
	result = table->stop;
	if (!safe_mutex_unlock(&table->stop_lock, "quit_now"))
		return (true);
	return (result);
}

bool	safe_usleep(int msec, const char *context)
{
	t_time	start;
	t_time	timestamp;

	if (!get_timestamp(&start) || !get_timestamp(&timestamp))
		return (false);
	while ((int)(timestamp - start) < msec)
	{
		if (usleep(100) == -1)
			return (error("usleep", context));
		if (!get_timestamp(&timestamp))
			return (false);
	}
	return (true);
}
