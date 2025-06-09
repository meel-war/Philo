#include "../include/philo.h"

/// usleep est de base en millisecondes donc x1000 conversion en microsecondes 
void *philo_loop(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    t_data *data = philo->data;

    int left = philo->id - 1;
    int right = (philo->id) % data->nb_philo;
    while(1)
    {
        pthread_mutex_lock(&data->death_mutex);
        if(data->someone_died)
        {
            pthread_mutex_unlock(&data->death_mutex);
            return (NULL);
        }
        pthread_mutex_unlock(&data->death_mutex);
        printf("Philosophe %d pense\n", philo->id);
        usleep(500000);
        if(philo->id % 2 == 0)
        {
            pthread_mutex_lock(&data->forks[left]);
            printf("Philosophe %d prend la fourchette gauche\n", philo->id);
            pthread_mutex_lock(&data->forks[right]);
            printf("Philosophe %d prend la fourchette droite\n", philo->id);
        }
        else
        {
            pthread_mutex_lock(&data->forks[right]);
            printf("Philosophe %d prend la fourchette droite\n", philo->id);
            pthread_mutex_lock(&data->forks[left]);
            printf("Philosophe %d prend la fourchette gauche\n", philo->id);
        }
        printf("Philosophe %d mange\n", philo->id);
        pthread_mutex_lock(&philo->meal_mutex);
        philo->last_meal = get_time();
        philo->meal_eaten++;
        pthread_mutex_unlock(&philo->meal_mutex);
        usleep(data->time_to_eat * 1000);
        pthread_mutex_unlock(&data->forks[left]);
        pthread_mutex_unlock(&data->forks[right]);
        printf("Philosophe %d dort\n", philo->id);
        usleep(data->time_to_sleep * 1000);
    }
    return(NULL);
}

void *philo_checker(void *checker)
{
    t_data *data = (t_data *)checker;
    int i;
    
    while(1)
    {
        i = 0;
        while(i < data->nb_philo)
        {
            pthread_mutex_lock(&data->philo[i].meal_mutex);
            if(get_time() - data->philo[i].last_meal > data->time_to_die)
            {
                pthread_mutex_lock(&data->death_mutex);
                data->someone_died = 1;
                pthread_mutex_unlock(&data->death_mutex);
                printf("Philosophe %d est mort\n", data->philo[i].id);
                pthread_mutex_unlock(&data->philo[i].meal_mutex);
                return (NULL);
            }
            pthread_mutex_unlock(&data->philo[i].meal_mutex);
            i++;
        }
        if(count_eat(data))
            return (NULL);
        usleep(1000);
    }
    return(NULL);
}

int initiate_philo(t_data *data)
{
    int i;
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
    i = 0;
    pthread_mutex_init(&data->death_mutex, NULL);
    while(i < data->nb_philo)
    {
        data->philo[i].id = i + 1;
        data->philo[i].last_meal = 0;
        data->philo[i].meal_eaten = 0;
        data->philo[i].data = data;
        pthread_mutex_init(&data->philo[i].meal_mutex, NULL);
        pthread_mutex_init(&data->forks[i], NULL);
        if (pthread_create(&data->philo[i].thread, NULL, philo_loop, &data->philo[i]))
        {
            free_all(data);
            return(1);
        }
        i++;
    }
     if (pthread_create(&data->checker_thread, NULL, philo_checker, data))
    {
        free_all(data);
        return(1);
     }
    return(0);
}

int main(int ac, char **av)
{
    t_data *data;
    int i;

    i = 0;
    data = malloc(sizeof(t_data));
    if(!data)
        return(1);
    memset(data, 0, sizeof(t_data));
    if (parse_args(ac, av, data) != 0)
    {
        free(data);
        return(1);
    }
    initiate_philo(data);
    while(i < data->nb_philo)
    {
        pthread_join(data->philo[i].thread, NULL);
        i++;
    }
    pthread_join(data->checker_thread, NULL);
    free_all(data);
    return(0);
}
