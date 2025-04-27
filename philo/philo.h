/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 22:11:04 by cwon              #+#    #+#             */
/*   Updated: 2025/04/27 20:44:56 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <errno.h>
# include <inttypes.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef pthread_mutex_t	t_mutex;
typedef struct s_philo	t_philo;
typedef struct s_table	t_table;
typedef struct timeval	t_timeval;
typedef uint64_t		t_time;
typedef void *(t_routine)(void *);

struct s_philo
{
	int			id;
	int			mealcount;
	pthread_t	thread;
	t_mutex		*fork1;
	t_mutex		*fork2;
	t_mutex		lastmeal_lock;
	t_table		*table;
	t_time		lastmeal;
};

struct s_table
{
	bool		stop;
	int			death_time;
	int			eat_time;
	int			min_meals;
	int			size;
	int			sleep_time;
	pthread_t	watchdog;
	t_mutex		*fork;
	t_mutex		mealcount_lock;
	t_mutex		print_lock;
	t_mutex		stop_lock;
	t_philo		*philo;
};

// flush.c
bool	error(const char *fn_name, const char *context);
bool	flush_mutex(t_table *table, int n, bool result);
bool	flush_philo(t_table *table, int n, bool result);
int		flush(t_table *table, bool mutex, int exit_status);

// init.c
bool	init_mutex(t_table *table);
bool	init_philo(t_table *table);
bool	init_table(t_table *table, int argc, char **argv);

// mutex.c
bool	safe_mutex_destroy(t_mutex *mutex, const char *context);
bool	safe_mutex_init(t_mutex *mutex, const char *context);
bool	safe_mutex_lock(t_mutex *mutex, const char *context);
bool	safe_mutex_unlock(t_mutex *mutex, const char *context);

// parse.c
bool	valid_args(int argc, char **argv);
int		ascii_to_nonneg_int(const char *str);

// philo_util.c
bool	get_timestamp(t_time *timestamp);
bool	print_log(t_philo *philo, const char *str);
bool	quit_now(t_table *table);
bool	safe_usleep(int msec, const char *context);
bool	update_last_meal(t_philo *philo);

// philo.c
int		philosophers(int argc, char **argv);

// routine_util.c
bool	grab_forks(t_philo *philo);
bool	release_forks(t_philo *philo, bool result);

// routine.c
void	*philo_routine(void *arg);

// thread.c
bool	safe_thread_create(pthread_t *thread, t_routine routine, void *arg, \
							const char *context);
bool	safe_thread_join(pthread_t thread, const char *context);

// watchdog.c
void	*watchdog_routine(void *arg);

#endif
