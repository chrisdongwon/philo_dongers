/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 20:53:22 by cwon              #+#    #+#             */
/*   Updated: 2025/04/27 20:53:24 by cwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static bool	is_positive_int(const char *str)
{
	const char	*int_max;
	size_t		i;

	i = 0;
	while (str[i])
	{
		if (i > 9 || str[i] < '0' || str[i] > '9')
			return (false);
		i++;
	}
	if (i == 10)
	{
		int_max = "2147483647";
		i = 0;
		while (str[i])
		{
			if (str[i] > int_max[i])
				return (false);
			i++;
		}
	}
	return (ascii_to_nonneg_int(str));
}

bool	valid_args(int argc, char **argv)
{
	int	i;

	if (argc != 5 && argc != 6)
	{
		printf("Error: Invalid number of arguments\n");
		return (false);
	}
	i = 0;
	while (++i < argc)
	{
		if (!is_positive_int(argv[i]))
		{
			printf("Error: All arguments must be positive integers\n");
			return (false);
		}
	}
	return (true);
}

int	ascii_to_nonneg_int(const char *str)
{
	int		result;
	size_t	i;

	i = 0;
	result = 0;
	while (str[i])
		result = (result * 10) + (str[i++] - '0');
	return (result);
}
