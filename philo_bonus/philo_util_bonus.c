/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_util_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 01:01:23 by cwon              #+#    #+#             */
/*   Updated: 2025/04/29 16:45:19 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

bool	get_timestamp(t_time *timestamp)
{
	t_timeval	tv;

	if (gettimeofday(&tv, 0))
		return (error("gettimeofday", "get_timestamp"));
	*timestamp = (t_time)(tv.tv_sec) * 1000 + (t_time)(tv.tv_usec) / 1000;
	return (true);
}

bool	kill_processes(t_table *table, int n, bool result)
{
	int	i;
	int	status;

	i = -1;
	while (++i < n)
	{
		if (!safe_kill(table->philo[i].pid, SIGKILL, "kill_processes"))
			result = false;
	}
	i = -1;
	while (++i < n)
	{
		if (!safe_waitpid(table->philo[i].pid, &status, 0, \
			"kill_processes") || (WIFEXITED(status) && WEXITSTATUS(status)))
			result = false;
	}
	return (result);
}

bool	print_log(t_philo *philo, const char *str)
{
	t_time	timestamp;

	if (!safe_sem_wait(philo->table->lock, "print_log") || \
		!get_timestamp(&timestamp))
		return (false);
	if (philo->alive && \
		(printf("%" PRIu64 " %d %s\n", timestamp, philo->id, str) <= 0))
	{
		safe_sem_post(philo->table->lock, "print_log");
		return (false);
	}
	return (safe_sem_post(philo->table->lock, "print_log"));
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
