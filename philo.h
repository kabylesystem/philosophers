#ifndef PHILO_H
# define PHILO_H

# include <p_thread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_philosopher t_philosopher;

typedef struct  s_table
{
    long    philo_nbr;
    long    time_to_die;
    long    time_to_eat;
    long    time_to_sleep;
    long    must_eat_count;
    long    start_time;
    int sim_stop;
    pthread_mutex_t sim_lock;
    pthread_mutex_t *forks;
    t_philo *philos;

}   t_table;

typedef struct  s_philosopher
{
    int id;
    int meals_eaten;
    long    last_meal;
    pthread_t   thread_id;
    pthread_mutex_t *l_fork;
    pthread_mutex_t *r_fork;
    t_rules *rules;
}   t_philosopher;

#endif 
