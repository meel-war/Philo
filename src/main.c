#include "../include/philo.h"

int is_digit(char **av, int ac)
{
    int i;
    int j;

    j = 1;
    while(j < ac)
    {
        i = 0;
        if(av[j][0] == '\0')
            return(0);
        while(av[j][i])
        {
            if(av[j][i] < '0' || av[j][i] > '9')
                return(0);
            i++;
        }
        j++;
    }
    return(1);
}

int philo_atoi(char *str)
{
    int result;
    int i;
    int before;

    result = 0;
    before = 0;
    i = 0;
    while(str[i] >= '0' && str[i] <= '9')
    {
        before = result;
        result *= 10;
        result += str[i] - '0';
        if(before > result)
            return(-2);
        i++;
    }
    return(result);
}

int parse_args(int ac, char **av, t_data *data)
{
    if(ac != 5 && ac != 6)
    {
        ft_putstr_fd("Error: Wrong number of arguments\n", 2);
        return(1);
    }
    if(!is_digit(av, ac))
    {
        ft_putstr_fd("Error: All arguments must be positive integers\n", 2);
        return(1);
    }
    data->nb_philo = philo_atoi(av[1]);
    data->time_to_die = philo_atoi(av[2]);
    data->time_to_eat = philo_atoi(av[3]);
    data->time_to_sleep = philo_atoi(av[4]);
    if(ac == 6)
        data->nb_must_eat = philo_atoi(av[5]);
    else
        data->nb_must_eat = -1;
    if(data->nb_philo == -2 || data->time_to_die == -2 || data->time_to_eat == -2 || data->time_to_sleep == -2 || data->nb_must_eat == -2)
    {
        ft_putstr_fd("Error: one argument is too big\n", 2);
        return(1);
    }
    return(0);
}

void *philo_loop(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    t_data *data = philo->data; // Pq ? sinon segfault
    while(1)
    {
        printf("Philosophe %d pense \n", philo->id);
        usleep(5000000);
        pthread_mutex_lock(&data->forks[philo->id - 1]);
        printf("Philosophe %d prend la fourchette de gauche \n", philo->id);
    }
}

int initiate_philo(t_data *data)
{
    int i;
    data->philo = malloc(data->nb_philo * (sizeof(t_philo)));
    if(!data->philo)
        return(1); // free
    memset(data->philo, 0, data->nb_philo * sizeof(t_philo));
    data->forks = malloc(data->nb_philo * sizeof(pthread_mutex_t));
    if(!data->forks)
        return(1); // free
    i = 0;
    while(i < data->nb_philo)
    {
        data->philo[i].id = i + 1;
        data->philo[i].last_meal = 0;
        data->philo[i].meal_eaten = 0;
        data->philo[i].data = data; // ??
        pthread_mutex_init(&data->forks[i], NULL);
        if (pthread_create(&data->philo[i].thread, NULL, philo_loop, &data->philo[i]))
        {
            //free data, philo et les mutex
            return(1);
        }
        i++;
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
    return(0);
}
