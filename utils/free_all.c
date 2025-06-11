#include "../include/philo.h"

void free_all(t_data *data)
{
    int i = 0;
    if(data)
    {
        if(data->forks)
        {
            while(i < data->nb_philo)
            {
                pthread_mutex_destroy(&data->forks[i]);
                i++;
            }
            free(data->forks);
        }
        i = 0;
        if(data->philo)
        {
            while(i < data->nb_philo)
            {
                pthread_mutex_destroy(&data->philo[i].meal_mutex);
                i++;
            }
            free(data->philo);
        }
        pthread_mutex_destroy(&data->death_mutex);
        pthread_mutex_destroy(&data->full_meal_mutex);
        free(data);
    }
}
