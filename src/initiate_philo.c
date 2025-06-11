#include "../include/philo.h"

static int allocate_philo_forks(t_data *data)
{
    data->philo = malloc(data->nb_philo * (sizeof(t_philo)));
    if(!data->philo)
    {
        free_all(data);
        return(1);
    }
    memset(data->philo, 0, data->nb_philo * sizeof(t_philo));
    data->forks = malloc(data->nb_philo * sizeof(pthread_mutex_t));
    if(!data->forks)
    {
        free_all(data);
        return(1);
    }
    return(0);
}

static void init_philo_value(int i, t_data *data)
{
        data->philo[i].id = i + 1;
        data->philo[i].left = i;
        data->philo[i].right = (i + 1) % data->nb_philo;
        data->philo[i].last_meal = 0;
        data->philo[i].meal_eaten = 0;
        data->philo[i].data = data;
        pthread_mutex_init(&data->philo[i].meal_mutex, NULL);
}
int initiate_philo(t_data *data)
{
    int i;

    i = 0;
    if(allocate_philo_forks(data) != 0)
        return(1);
    pthread_mutex_init(&data->death_mutex, NULL);
    pthread_mutex_init(&data->full_meal_mutex, NULL);
    while(i < data->nb_philo)
    {
        init_philo_value(i, data);
        pthread_mutex_init(&data->forks[i], NULL);
        i++;
    }
    return(0);
}
