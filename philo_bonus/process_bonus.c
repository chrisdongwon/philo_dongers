/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 12:21:32 by cwon              #+#    #+#             */
/*   Updated: 2025/04/29 12:34:51 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

bool	safe_kill(pid_t pid, int sig, const char *context)
{
	if (kill(pid, sig) == -1)
		return (error("kill", context));
	return (true);
}

bool	safe_waitpid(pid_t pid, int *wstatus, int options, const char *context)
{
	if (waitpid(pid, wstatus, options) == -1)
		return (error("waitpid", context));
	return (true);
}
