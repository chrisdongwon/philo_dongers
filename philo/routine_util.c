/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 20:03:25 by cwon              #+#    #+#             */
/*   Updated: 2025/04/27 20:45:21 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	grab_first_fork(t_philo *philo)
{
	if (!safe_mutex_lock(philo->fork1, "grab_first_fork"))
		return (false);
	if (!print_log(philo, "has taken a fork"))
	{
		safe_mutex_unlock(philo->fork1, "grab_first_fork");
		return (false);
	}
	return (true);
}

static bool	grab_second_fork(t_philo *philo)
{
	if (!safe_mutex_lock(philo->fork2, "grab_second_fork"))
	{
		safe_mutex_unlock(philo->fork1, "grab_second_fork");
		return (false);
	}
	if (!print_log(philo, "has taken a fork"))
		return (release_forks(philo, false));
	return (true);
}

bool	grab_forks(t_philo *philo)
{
	return (grab_first_fork(philo) && grab_second_fork(philo));
}

bool	release_forks(t_philo *philo, bool result)
{
	if (!safe_mutex_unlock(philo->fork1, "release_forks"))
		result = false;
	if (!safe_mutex_unlock(philo->fork2, "release_forks"))
		result = false;
	return (result);
}

bool	update_last_meal(t_philo *philo)
{
	if (!safe_mutex_lock(&philo->lastmeal_lock, "philo_routine"))
		return (false);
	if (!get_timestamp(&philo->lastmeal))
	{
		safe_mutex_unlock(&philo->lastmeal_lock, "philo_routine");
		return (false);
	}
	return (safe_mutex_unlock(&philo->lastmeal_lock, "philo_routine"));
}
