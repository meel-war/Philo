#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data t_data;

typedef struct s_philo
{
    int     id;
    long long last_meal;
    int       meal_eaten;
    pthread_t   thread;
    t_data      *data;
}       t_philo;

typedef struct s_data
{
    int         nb_philo;
    int         time_to_die;
    int         time_to_eat;
    int         time_to_sleep;
    int         nb_must_eat;
    int         someone_died;
    pthread_mutex_t *forks;
    pthread_t   checker_thread;
    t_philo     *philo;
}               t_data;


void	ft_putstr_fd(char *s, int fd);
long long get_time(void);
int count_eat(t_data *data);

#endif