#include "../include/philo.h"

int count_eat(t_data *data)
{
    int i;


    if(data->nb_must_eat == -1)
        return (0);
    i = 0;
    while(i < data->nb_philo)
    {
        if(data->philo[i].meal_eaten < data->nb_must_eat)
            return(0);
        i++;
    }
    printf("Tous les philosophes ont mangé au moins %d fois\n", data->nb_must_eat);
    return (1);
}
