/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:24:45 by cwon              #+#    #+#             */
/*   Updated: 2025/04/12 18:51:07 by cwon             ###   ########.fr       */
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
	int			mealcount;
	pthread_t	thread;
	t_table		*table;
	t_time		lastmeal;
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
	t_mutex		lastmeal_lock;
	t_mutex		mealcount_lock;
	t_mutex		stop_lock;
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
bool	mealcount_check(t_philo *philo);
bool	release_forks(t_philo *philo);
bool	release_forks_quit(t_philo *philo);
void	choose_forks(t_philo *philo, int *first, int *second);

// routine.c
void	*philo_routine(void *arg);

// thread.c
bool	safe_thread_create(pthread_t *thread, t_routine routine, void *arg);
bool	safe_thread_join(pthread_t thread);

// time.c
bool	get_timestamp(t_llong *timestamp, t_philo *philo);
bool	safe_gettimeofday(t_time *tv);
bool	safe_usleep(int ms);
long	time_diff(t_time *start, t_time *end);

// watchdog.c
void	*terminate(t_table *table, int i, bool is_dead);
void	*watchdog_routine(void *arg);

#endif