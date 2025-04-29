/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 19:11:43 by cwon              #+#    #+#             */
/*   Updated: 2025/04/27 21:18:54 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	philo_eat(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	if (!grab_forks(philo))
		return (false);
	if (!print_log(philo, "is eating") || \
		!safe_mutex_lock(&philo->lastmeal_lock, "philo_eat"))
		return (release_forks(philo, false));
	if (!get_timestamp(&philo->lastmeal) || \
		!safe_mutex_lock(&table->mealcount_lock, "philo_eat"))
	{
		safe_mutex_unlock(&philo->lastmeal_lock, "philo_eat");
		return (release_forks(philo, false));
	}
	philo->mealcount++;
	if (!safe_mutex_unlock(&table->mealcount_lock, "philo_eat"))
	{
		safe_mutex_unlock(&philo->lastmeal_lock, "philo_eat");
		return (release_forks(philo, false));
	}
	if (!safe_mutex_unlock(&philo->lastmeal_lock, "philo_eat") || \
		!safe_usleep(table->eat_time, "philo_eat"))
		return (release_forks(philo, false));
	return (release_forks(philo, true));
}

static bool	philo_sleep(t_philo *philo)
{
	return (print_log(philo, "is sleeping") && \
			safe_usleep(philo->table->sleep_time, "philo_sleep"));
}

static bool	philo_think(t_philo *philo)
{
	return (print_log(philo, "is thinking"));
}

static void	*single_philo(t_philo *philo)
{
	print_log(philo, "is thinking");
	if (!safe_mutex_lock(philo->table->fork, "single_philo"))
		return (0);
	print_log(philo, "has taken a fork");
	safe_mutex_unlock(philo->table->fork, "single_philo");
	return (0);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (!update_lastmeal(philo))
		return (0);
	if (philo->table->size == 1)
		return (single_philo(philo));
	if (philo->id % 2 == 0 && !safe_usleep(1, "philo_routine"))
		return (0);
	while (!quit_now(philo->table))
	{
		if (!philo_think(philo) || !philo_eat(philo) || !philo_sleep(philo))
			break ;
	}
	return (0);
}
