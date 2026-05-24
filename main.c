/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynabti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 23:52:12 by ynabti            #+#    #+#             */
/*   Updated: 2026/05/20 17:59:41 by ynabti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc != 5 && argc != 6)
	{
		printf("Error: usage: ./philo n_philo die eat sleep [must_eat]\n");
		return (1);
	}
	if (parse_args(&table, argc, argv))
	{
		printf("Error: arguments must be valid positive integers\n");
		return (1);
	}
	if (init_table(&table))
	{
		printf("Error: initialization failed\n");
		return (1);
	}
	start_simulation(&table);
	cleanup(&table);
	return (0);
}
