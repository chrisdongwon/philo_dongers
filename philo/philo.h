/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:24:45 by cwon              #+#    #+#             */
/*   Updated: 2025/04/10 13:59:28 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <errno.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef long long		t_llong;
typedef pthread_mutex_t	t_mutex;
typedef struct s_philo	t_philo;
typedef struct s_table	t_table;
typedef struct timeval	t_time;
typedef void *(t_routine)(void *);

struct s_philo
{
	int			id;
	int			meal_count;
	pthread_t	thread;
	t_table		*table;
	t_time		last_meal;
};

struct s_table
{
	bool		stop;
	int			death_time;
	int			eat_time;
	int			min_meals;
	int			min_reached;
	int			size;
	int			sleep_time;
	pthread_t	watchdog;
	t_mutex		*fork;
	t_mutex		lock;
	t_mutex		mealcount_lock;
	t_philo		*philo;
};

// init.c
bool	init_mutex(t_table *table);
bool	init_param(int argc, char **argv, t_table *table);
bool	init_philo(t_table *table);

// mutex.c
bool	safe_mutex_destroy(t_mutex *mutex);
bool	safe_mutex_init(t_mutex *mutex);
bool	safe_mutex_lock(t_mutex *mutex);
bool	safe_mutex_unlock(t_mutex *mutex);

// parse.c
bool	valid_args(int argc, char **argv);
int		ascii_to_nonneg_int(const char *nptr);

// philo.c
bool	error(const char *str);
int		philosophers(int argc, char **argv);

// routine_util.c
bool	grab_fork(t_philo *philo, int fork_number);
bool	release_forks(t_philo *philo);
bool	update_mealcount(t_philo *philo);
void	choose_forks(t_philo *philo, int *first, int *second);

// routine.c
void	*philo_routine(void *arg);

// thread.c
bool	safe_thread_create(pthread_t *thread, t_routine routine, void *arg);
bool	safe_thread_join(pthread_t thread);

// time.c
bool	get_timestamp_ms(t_llong *timestamp, t_philo *philo);
bool	safe_gettimeofday(t_time *tv);
bool	safe_usleep(int msec);
long	time_diff_ms(t_time *start, t_time *end);

// watchdog.c
void	*watchdog_routine(void *arg);

#endif