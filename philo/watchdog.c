/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watchdog.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 02:41:46 by cwon              #+#    #+#             */
/*   Updated: 2025/04/27 19:43:16 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	exceeded_death_time(t_philo *philo)
{
	t_time	timestamp;

	if (!safe_mutex_lock(&philo->lastmeal_lock, "exceeded_death_time"))
		return (true);
	if (!get_timestamp(&timestamp) || \
		((int)(timestamp - philo->lastmeal) > philo->table->death_time))
	{
		safe_mutex_unlock(&philo->lastmeal_lock, "exceeded_death_time");
		return (true);
	}
	return (!safe_mutex_unlock(&philo->lastmeal_lock, "exceeded_death_time"));
}

static bool	min_reached(t_table *table)
{
	int		i;
	int		count;
	t_philo	*philo;

	i = -1;
	count = 0;
	while (++i < table->size)
	{
		philo = &table->philo[i];
		if (!safe_mutex_lock(&table->mealcount_lock, "min_reached"))
			return (true);
		if ((table->min_meals != -1) && (philo->mealcount >= table->min_meals))
			count++;
		if (!safe_mutex_unlock(&table->mealcount_lock, "min_reached"))
			return (true);
	}
	if (count == table->size)
	{
		if (!safe_mutex_lock(&table->stop_lock, "min_reached"))
			return (true);
		table->stop = true;
		safe_mutex_unlock(&table->stop_lock, "min_reached");
		return (true);
	}
	return (false);
}

static bool	starvation_detected(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while (++i < table->size)
	{
		philo = &table->philo[i];
		if (exceeded_death_time(philo))
		{
			if (!quit_now(table))
			{
				print_log(philo, "is dead");
				if (!safe_mutex_lock(&table->stop_lock, "min_reached"))
					return (true);
				table->stop = true;
				safe_mutex_unlock(&table->stop_lock, "min_reached");
				return (true);
			}
			return (true);
		}
	}
	return (false);
}

void	*watchdog_routine(void *arg)
{
	t_table	*table;

	table = (t_table *)arg;
	while (!starvation_detected(table) && !min_reached(table))
		continue ;
	return (0);
}
