/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynabti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 18:03:14 by ynabti            #+#    #+#             */
/*   Updated: 2026/05/21 07:03:26 by ynabti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

static void	print_died(t_philo *philo)
{
	long	timestamp;

	pthread_mutex_lock(&philo->table->print_lock);
	timestamp = get_time_ms() - philo->table->start_time;
	printf("%ld %d died\n", timestamp, philo->id);
	pthread_mutex_unlock(&philo->table->print_lock);
}

static int	all_ate_enough(t_table *table)
{
	int	i;
	int	full;

	if (table->must_eat_count == -1)
		return (0);
	i = 0;
	full = 0;
	while (i < table->philo_nbr)
	{
		pthread_mutex_lock(&table->philos[i].meal_lock);
		if (table->philos[i].meals_eaten >= table->must_eat_count)
			full++;
		pthread_mutex_unlock(&table->philos[i].meal_lock);
		i++;
	}
	if (full == table->philo_nbr)
		return (set_sim_stop(table), 1);
	return (0);
}

static void	monitor(t_table *table)
{
	int		i;
	long	now;

	while (1)
	{
		i = 0;
		while (i < table->philo_nbr)
		{
			pthread_mutex_lock(&table->philos[i].meal_lock);
			now = get_time_ms();
			if (now - table->philos[i].last_meal > table->time_to_die)
			{
				pthread_mutex_unlock(&table->philos[i].meal_lock);
				set_sim_stop(table);
				return (print_died(&table->philos[i]));
			}
			pthread_mutex_unlock(&table->philos[i].meal_lock);
			i++;
		}
		if (all_ate_enough(table))
			return ;
		usleep(500);
	}
}

int	start_simulation(t_table *table)
{
	int	i;
	int	created;

	table->start_time = get_time_ms();
	created = 0;
	while (created < table->philo_nbr)
	{
		table->philos[created].last_meal = table->start_time;
		if (pthread_create(&table->philos[created].thread, NULL,
				philo_routine, &table->philos[created]) != 0)
		{
			set_sim_stop(table);
			break ;
		}
		created++;
	}
	if (created == table->philo_nbr)
		monitor(table);
	i = 0;
	while (i < created)
		pthread_join(table->philos[i++].thread, NULL);
	return (created != table->philo_nbr);
}
