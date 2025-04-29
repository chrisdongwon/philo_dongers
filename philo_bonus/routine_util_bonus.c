/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_util_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:52:15 by cwon              #+#    #+#             */
/*   Updated: 2025/04/29 16:43:04 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

bool	grab_first_fork(t_philo *philo)
{
	if (!safe_sem_wait(philo->table->forks, "grab_first_fork"))
		return (false);
	if (!print_log(philo, "has taken a fork"))
	{
		safe_sem_post(philo->table->forks, "grab_first_fork");
		return (false);
	}
	return (true);
}

bool	grab_second_fork(t_philo *philo)
{
	if (!safe_sem_wait(philo->table->forks, "grab_second_fork"))
	{
		safe_sem_post(philo->table->forks, "grab_second_fork");
		return (false);
	}
	if (!print_log(philo, "has taken a fork"))
		return (release_forks(philo, false));
	return (true);
}

bool	release_forks(t_philo *philo, bool result)
{
	if (!safe_sem_post(philo->table->forks, "release_forks"))
		result = false;
	if (!safe_sem_post(philo->table->forks, "release_forks"))
		result = false;
	return (result);
}

bool	update_lastmeal(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	if (!safe_sem_wait(table->lock, "update_lastmeal"))
		return (false);
	if (!get_timestamp(&philo->lastmeal))
	{
		safe_sem_post(table->lock, "update_lastmeal");
		return (false);
	}
	return (safe_sem_post(table->lock, "update_lastmeal"));
}

bool	update_mealcount(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	if (!safe_sem_wait(table->lock, "update_mealcount"))
		return (false);
	philo->mealcount++;
	return (safe_sem_post(table->lock, "update_mealcount"));
}
