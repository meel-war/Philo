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
    int     left;
    int     right;
    long long last_meal;
    int       meal_eaten;
    pthread_mutex_t meal_mutex;
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
    int         finish_eat;
    int         full_meal;
    long long   start;
    pthread_mutex_t *forks;
    pthread_t   checker_thread;
    pthread_mutex_t death_mutex;
     pthread_mutex_t    full_meal_mutex; 
    t_philo     *philo;
}               t_data;


void	ft_putstr_fd(char *s, int fd);
long long get_time(void);
int count_eat(t_data *data, t_philo *philo); 
t_data *parse_args(int ac, char **av);          
int initiate_philo(t_data *data);  
int link_thread(t_data *data);     
void free_all(t_data *data);
void *philo_loop(void *arg);
void *philo_checker(void *checker);
int is_digit(char **av, int ac);
int philo_atoi(char *str);

#endif