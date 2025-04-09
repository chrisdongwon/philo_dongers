/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 10:35:45 by cwon              #+#    #+#             */
/*   Updated: 2025/04/09 12:20:17 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	grab_fork(t_philo *philo, int fork_number)
{
	bool	quit;
	t_llong	timestamp;
	t_table	*table;

	table = philo->table;
	if (!safe_mutex_lock(&table->lock))
		return (false);
	quit = table->stop;
	if (!safe_mutex_unlock(&table->lock) || quit || \
		!safe_mutex_lock(&table->fork[fork_number]) || \
		!get_timestamp_ms(&timestamp, 0))
		return (false);
	printf("%lld %d has picked up a fork\n", timestamp, philo->id + 1);
	return (true);
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

bool	update_mealcount(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	philo->meal_count++;
	if (philo->meal_count != table->min_meals)
		return (true);
	if (!safe_mutex_lock(&table->lock))
		return (false);
	table->min_reached++;
	if (table->min_reached == table->size)
	{
		safe_mutex_lock(&table->mealcount_lock);
		table->stop = true;
		safe_mutex_unlock(&table->mealcount_lock);
		safe_mutex_unlock(&table->lock);
		return (false);
	}
	return (safe_mutex_unlock(&table->lock));
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
