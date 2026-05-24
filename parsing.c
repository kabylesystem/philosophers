/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynabti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 13:34:12 by ynabti            #+#    #+#             */
/*   Updated: 2026/05/09 20:52:56 by ynabti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

static int	is_valid_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static long	ft_atol(char *str)
{
	long	res;
	int		i;

	res = 0;
	i = 0;
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		res = res * 10 + (str[i] - '0');
		if (res > 2147483647)
			return (2147483648);
		i++;
	}
	return (res);
}

int	parse_args(t_table *table, int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!is_valid_number(argv[i]))
			return (1);
		i++;
	}
	table->philo_nbr = ft_atol(argv[1]);
	table->time_to_die = ft_atol(argv[2]);
	table->time_to_eat = ft_atol(argv[3]);
	table->time_to_sleep = ft_atol(argv[4]);
	table->must_eat_count = -1;
	if (argc == 6)
		table->must_eat_count = ft_atol(argv[5]);
	if (table->philo_nbr < 1 || table->philo_nbr > 2147483647
		|| table->time_to_die < 1 || table->time_to_die > 2147483647
		|| table->time_to_eat < 1 || table->time_to_eat > 2147483647
		|| table->time_to_sleep < 1 || table->time_to_sleep > 2147483647
		|| table->must_eat_count > 2147483647)
		return (1);
	return (0);
}
