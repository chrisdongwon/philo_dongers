/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:16:38 by cwon              #+#    #+#             */
/*   Updated: 2025/04/17 17:16:46 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static bool	is_positive_int(const char *s)
{
	const char	*uint_max;
	int			i;

	i = 0;
	while (s[i])
	{
		if (i > 9 || s[i] < '0' || s[i] > '9')
			return (false);
		i++;
	}
	if (i == 10)
	{
		uint_max = "2147483647";
		i = 0;
		while (s[i])
		{
			if (s[i] > uint_max[i])
				return (false);
			i++;
		}
	}
	return (ascii_to_nonneg_int(s));
}

bool	valid_args(int argc, char **argv)
{
	int	i;

	if (argc != 5 && argc != 6)
	{
		printf("error: invalid number of arguments\n");
		return (false);
	}
	i = 0;
	while (++i < argc)
	{
		if (!is_positive_int(argv[i]))
		{
			printf("error: all arguments must be positive integers\n");
			return (false);
		}
	}
	return (true);
}

int	ascii_to_nonneg_int(const char *nptr)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	while (nptr[i])
		result = (result * 10) + (nptr[i++] - '0');
	return (result);
}
