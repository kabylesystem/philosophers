/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynabti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 10:10:50 by ynabti            #+#    #+#             */
/*   Updated: 2026/05/07 08:23:48 by ynabti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

int	sim_is_running(t_table *table)
{
	int	running;

	pthread_mutex_lock(&table->sim_lock);
	running = !table->sim_stop;
	pthread_mutex_unlock(&table->sim_lock);
	return (running);
}

void	set_sim_stop(t_table *table)
{
	pthread_mutex_lock(&table->sim_lock);
	table->sim_stop = 1;
	pthread_mutex_unlock(&table->sim_lock);
}

void	print_status(t_philo *philo, char *status)
{
	long	timestamp;

	pthread_mutex_lock(&philo->table->print_lock);
	if (sim_is_running(philo->table))
	{
		timestamp = get_time_ms() - philo->table->start_time;
		printf("%ld %d %s\n", timestamp, philo->id, status);
	}
	pthread_mutex_unlock(&philo->table->print_lock);
}
