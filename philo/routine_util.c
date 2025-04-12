/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 10:35:45 by cwon              #+#    #+#             */
/*   Updated: 2025/04/12 18:58:04 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	grab_fork(t_philo *philo, int fork_number)
{
	t_llong	timestamp;
	t_table	*table;

	table = philo->table;
	if (!safe_mutex_lock(&table->fork[fork_number]) || \
		!get_timestamp(&timestamp, 0))
		return (false);
	if (!safe_mutex_lock(&table->stop_lock))
	{
		safe_mutex_unlock(&table->fork[fork_number]);
		return (false);
	}
	if (table->stop)
	{
		safe_mutex_unlock(&table->stop_lock);
		safe_mutex_unlock(&table->fork[fork_number]);
		return (false);
	}
	if (!safe_mutex_unlock(&table->stop_lock))
	{
		safe_mutex_unlock(&table->fork[fork_number]);
		return (false);
	}
	printf("%lld %d has picked up a fork\n", timestamp, philo->id + 1);
	return (true);
}

bool	mealcount_check(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	philo->mealcount++;
	if (!safe_mutex_lock(&table->mealcount_lock))
		return (false);
	if (philo->mealcount == table->min_meals)
		table->min_reached++;
	if (table->min_reached == table->size)
		terminate(table, philo->id, false);
	return (safe_mutex_unlock(&table->mealcount_lock));
}

bool	release_forks(t_philo *philo)
{
	int		first;
	int		second;
	t_table	*table;

	table = philo->table;
	choose_forks(philo, &first, &second);
	return (safe_mutex_unlock(&table->fork[first]) && \
			safe_mutex_unlock(&table->fork[second]));
}

bool	release_forks_quit(t_philo *philo)
{
	release_forks(philo);
	return (false);
}

void	choose_forks(t_philo *philo, int *first, int *second)
{
	int		temp;
	t_table	*table;

	table = philo->table;
	*first = philo->id;
	*second = (philo->id + 1) % table->size;
	if (*first > *second)
	{
		temp = *first;
		*first = *second;
		*second = temp;
	}
}
