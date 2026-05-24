/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynabti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 00:44:22 by ynabti            #+#    #+#             */
/*   Updated: 2026/05/16 18:16:30 by ynabti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_table	t_table;

typedef struct s_philo
{
	int				id;
	long			meals_eaten;
	long			last_meal;
	pthread_t		thread;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	meal_lock;
	t_table			*table;
}	t_philo;

typedef struct s_table
{
	long			philo_nbr;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			must_eat_count;
	long			start_time;
	int				sim_stop;
	pthread_mutex_t	sim_lock;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	*forks;
	t_philo			*philos;
}	t_table;

/* parsing.c */
int		parse_args(t_table *table, int argc, char **argv);

/* init.c */
int		init_table(t_table *table);
void	cleanup(t_table *table);

/* time.c */
long	get_time_ms(void);
void	ft_usleep(long ms);

/* utils.c */
void	print_status(t_philo *philo, char *status);
int		sim_is_running(t_table *table);
void	set_sim_stop(t_table *table);

/* routine.c */
void	*philo_routine(void *arg);

/* threads.c */
int		start_simulation(t_table *table);

#endif
