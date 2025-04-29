/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 20:59:43 by cwon              #+#    #+#             */
/*   Updated: 2025/04/29 16:27:48 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <errno.h>
# include <fcntl.h>
# include <inttypes.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>

# define FORKS_SEM	"/forks"
# define LOCK_SEM	"/lock"
# define QUIT_SEM	"/quit"

typedef struct s_philo	t_philo;
typedef struct s_table	t_table;
typedef struct timeval	t_timeval;
typedef uint64_t		t_time;
typedef void *(t_routine)(void *);

struct s_philo
{
	bool		alive;
	bool		min_reached;
	int			id;
	int			mealcount;
	pid_t		pid;
	pthread_t	watchdog;
	t_table		*table;
	t_time		lastmeal;
};

struct s_table
{
	int		death_time;
	int		eat_time;
	int		min_meals;
	int		size;
	int		sleep_time;
	sem_t	*forks;
	sem_t	*lock;
	sem_t	*quit;
	t_philo	*philo;
};

// flush_bonus.c
bool	error(const char *fn_name, const char *context);
int		flush_routine(t_table *table, int exit_status);
int		flush(t_table *table, bool sem, int exit_status);

// init_bonus.c
bool	init_philo(t_table *table);
bool	init_sem(t_table *table);
bool	init_table(t_table *table, int argc, char **argv);

// parse_bonus.c
bool	valid_args(int argc, char **argv);
int		ascii_to_nonneg_int(const char *nptr);

// philo_bonus.c
int		philosophers(int argc, char **argv);

// philo_util_bonus.c
bool	get_timestamp(t_time *timestamp);
bool	kill_processes(t_table *table, int n, bool result);
bool	print_log(t_philo *philo, const char *str);
bool	safe_usleep(int msec, const char *context);

// process_bonus.c
bool	safe_kill(pid_t	pid, int sig, const char *context);
bool	safe_waitpid(pid_t pid, int *wstatus, int options, const char *context);

// routine_bonus.c
void	philo_routine(t_philo *philo);

// routine_util_bonus.c
bool	grab_first_fork(t_philo *philo);
bool	grab_second_fork(t_philo *philo);
bool	release_forks(t_philo *philo, bool result);
bool	update_lastmeal(t_philo *philo);
bool	update_mealcount(t_philo *philo);

// semaphore_bonus.c
bool	safe_sem_close(sem_t *sem, const char *context);
bool	safe_sem_post(sem_t *sem, const char *context);
bool	safe_sem_unlink(const char *sem_name, const char *context);
bool	safe_sem_wait(sem_t	*sem, const char *context);

// thread_bonus.c
bool	safe_thread_create(pthread_t *thread, t_routine routine, void *arg, \
							const char *context);
bool	safe_thread_detach(pthread_t thread, const char *context);

// watchdog_bonus.c
void	*watchdog_routine(void *arg);

#endif
