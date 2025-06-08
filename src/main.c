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

/// usleep est de base en millisecondes donc x1000 conversion en microsecondes 
void *philo_loop(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    t_data *data = philo->data;

    int left = philo->id - 1;
    int right = (philo->id) % data->nb_philo;
    while(1)
    {
        if(data->someone_died == 1)
            return (NULL);
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
        philo->last_meal = get_time();
        philo->meal_eaten++;
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
            data->philo->last_meal;
            if(get_time() - data->philo[i].last_meal > data->time_to_die)
            {
                data->someone_died = 1;
                printf("Philosophe %d est mort\n", data->philo[i].id);
                return (NULL);
            }
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
     if (pthread_create(&data->checker_thread, NULL, philo_checker, data))
    {
        //free data, philo et les mutex
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
    return(0);
}
