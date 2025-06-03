/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 21:03:37 by cwon              #+#    #+#             */
/*   Updated: 2025/06/03 16:56:01 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static bool	philo_eat(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	if (!grab_first_fork(philo) || !grab_second_fork(philo))
		return (false);
	if (!print_log(philo, "is eating") || \
!update_lastmeal(philo) || !safe_usleep(table->eat_time, "philo_eat") || \
!update_mealcount(philo))
		return (release_forks(philo, false));
	if (philo->mealcount == table->min_meals && \
!safe_sem_post(table->quit, "philo_eat"))
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

void	philo_routine(t_philo *philo)
{
	if (!safe_thread_create(&philo->watchdog, watchdog_routine, philo, \
"philo_routine") || !safe_thread_detach(philo->watchdog, "philo_routine") || \
!update_lastmeal(philo) || \
(philo->id % 2 == 0 && !safe_usleep(1, "philo_routine")))
		exit(flush_routine(philo->table, EXIT_FAILURE));
	while (philo_think(philo) && philo_eat(philo) && philo_sleep(philo) && \
safe_usleep(1, "philo_routine"))
		continue ;
	exit(flush_routine(philo->table, EXIT_SUCCESS));
}
