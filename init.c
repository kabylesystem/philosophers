/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynabti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 03:37:31 by ynabti            #+#    #+#             */
/*   Updated: 2026/05/17 04:06:41 by ynabti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

static void	init_philos(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_nbr)
	{
		table->philos[i].id = i + 1;
		table->philos[i].meals_eaten = 0;
		table->philos[i].last_meal = 0;
		table->philos[i].table = table;
		table->philos[i].l_fork = &table->forks[i];
		table->philos[i].r_fork = &table->forks[(i + 1) % table->philo_nbr];
		pthread_mutex_init(&table->philos[i].meal_lock, NULL);
		i++;
	}
}

int	init_table(t_table *table)
{
	int	i;

	table->sim_stop = 0;
	table->forks = malloc(sizeof(pthread_mutex_t) * table->philo_nbr);
	table->philos = malloc(sizeof(t_philo) * table->philo_nbr);
	if (!table->forks || !table->philos)
		return (1);
	if (pthread_mutex_init(&table->sim_lock, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&table->print_lock, NULL) != 0)
		return (1);
	i = 0;
	while (i < table->philo_nbr)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
			return (1);
		i++;
	}
	init_philos(table);
	return (0);
}

void	cleanup(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_nbr)
	{
		pthread_mutex_destroy(&table->forks[i]);
		pthread_mutex_destroy(&table->philos[i].meal_lock);
		i++;
	}
	pthread_mutex_destroy(&table->sim_lock);
	pthread_mutex_destroy(&table->print_lock);
	free(table->forks);
	free(table->philos);
}
