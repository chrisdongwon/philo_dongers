/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:07:03 by cwon              #+#    #+#             */
/*   Updated: 2025/04/22 22:45:25 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <errno.h>
# include <fcntl.h>
# include <semaphore.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>

# define ALIVE_SEM "/alive_sem"
# define DEATH_SEM "/death_sem"
# define FORKS_SEM "/forks_sem"

typedef struct s_table	t_table;

struct s_table
{
	int		death_time;
	int		eat_time;
	int		min_meals;
	int		size;
	int		sleep_time;
	pid_t	*philo;
	sem_t	*death;
	sem_t	*forks;
};

// flush_bonus.c
bool	error(const char *str);
int		flush(t_table *table, bool flush_sem, int exit_status);

// init_bonus.c
bool	init_sem(t_table *table);
bool	init_table(int argc, char **argv, t_table *table);

// parse_bonus.c
bool	valid_args(int argc, char **argv);
int		ascii_to_nonneg_int(const char *nptr);

// philo_bonus.c
int		philosophers(int argc, char **argv);

// semaphore_bonus.c
bool	safe_sem_close(sem_t *sem);
bool	safe_sem_unlink(const char *name);
sem_t	*safe_sem_open(const char *name, unsigned int value);
void	sem_close_and_unlink(sem_t *sem, const char *sem_name);

#endif