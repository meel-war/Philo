#include "../include/philo.h"

static int is_digit(char **av, int ac)
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

static int philo_atoi(char *str)
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
static int check_args(int ac, char **av)
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
    return(0);
}

static void initalise_args(int ac, char **av, t_data *data)
{
    data->nb_philo = philo_atoi(av[1]);
    data->time_to_die = philo_atoi(av[2]);
    data->time_to_eat = philo_atoi(av[3]);
    data->time_to_sleep = philo_atoi(av[4]);
    if(ac == 6)
        data->nb_must_eat = philo_atoi(av[5]);
    else
        data->nb_must_eat = -1;
    pthread_mutex_init(&data->death_mutex, NULL);
}

int parse_args(int ac, char **av, t_data *data)
{
    data = malloc(sizeof(t_data));
    if(!data)
        return(1);
    memset(data, 0, sizeof(t_data));
    if(check_args(av, ac))
    {
        free(data);
        return(1);
    }
    initialise_args(ac, av, data);
    if(data->nb_philo == -2 || data->time_to_die == -2 || data->time_to_eat == -2 || data->time_to_sleep == -2 || data->nb_must_eat == -2)
    {
        ft_putstr_fd("Error: one argument is too big\n", 2);
        return(1);
    }
    return(0);
}
