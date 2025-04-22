/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 14:43:05 by cwon              #+#    #+#             */
/*   Updated: 2025/04/22 23:30:15 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	philo_eat(t_philo *philo)
{
	t_llong	timestamp;
	t_table	*table;

	table = philo->table;
	if (!safe_mutex_lock(&table->stop_lock, "philo_eat"))
		return (release_forks_quit(philo));
	if (table->stop || !safe_mutex_unlock(&table->stop_lock, "philo_eat"))
		return (release_forks_quit(philo));
	if (get_timestamp(&timestamp, philo))
		printf("%lld %d is eating\n", timestamp, philo->id + 1);
	else
		return (release_forks_quit(philo));
	if ((table->min_meals && !mealcount_check(philo)) || \
		!safe_usleep(table->eat_time, "philo_eat"))
		return (release_forks_quit(philo));
	return (release_forks(philo));
}

static bool	philo_forks(t_philo *philo)
{
	int		first;
	int		second;

	choose_forks(philo, &first, &second);
	if (!grab_fork(philo, first))
		return (false);
	if ((first == second) || !grab_fork(philo, second))
	{
		safe_mutex_unlock(&philo->table->fork[first], "philo_forks");
		return (false);
	}
	return (true);
}

static bool	philo_sleep(t_philo *philo)
{
	t_llong	timestamp;
	t_table	*table;

	table = philo->table;
	if (!safe_mutex_lock(&table->stop_lock, "philo_sleep"))
		return (false);
	if (!get_timestamp(&timestamp, 0) || table->stop)
	{
		safe_mutex_unlock(&table->stop_lock, "philo_sleep");
		return (false);
	}
	if (!safe_mutex_unlock(&table->stop_lock, "philo_sleep"))
		return (false);
	printf("%lld %d is sleeping\n", timestamp, philo->id + 1);
	return (safe_usleep(table->sleep_time, "philo_sleep"));
}

static bool	philo_think(t_philo *philo)
{
	t_llong	timestamp;
	t_table	*table;

	table = philo->table;
	if (!safe_mutex_lock(&table->stop_lock, "philo_think"))
		return (false);
	if (!get_timestamp(&timestamp, 0) || table->stop)
	{
		safe_mutex_unlock(&table->stop_lock, "philo_think");
		return (false);
	}
	if (!safe_mutex_unlock(&table->stop_lock, "philo_think"))
		return (false);
	printf("%lld %d is thinking\n", timestamp, philo->id + 1);
	return (true);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo_think(philo) && philo_forks(philo) && philo_eat(philo) && \
			philo_sleep(philo))
		continue ;
	return (0);
}
