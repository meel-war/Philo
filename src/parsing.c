#include "../include/philo.h"

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

static void initialise_args(int ac, char **av, t_data *data)
{
    data->nb_philo = philo_atoi(av[1]);
    data->time_to_die = philo_atoi(av[2]);
    data->time_to_eat = philo_atoi(av[3]);
    data->time_to_sleep = philo_atoi(av[4]);
    if(ac == 6)
        data->nb_must_eat = philo_atoi(av[5]);
    else
        data->nb_must_eat = -1;
}

static int validate_values(t_data *data)
{
    if (data->nb_philo <= 0)
    {
        ft_putstr_fd("Error: Number of philosophers must be positive\n", 2);
        return(1);
    }
    if (data->time_to_die <= 0 || data->time_to_eat <= 0 || data->time_to_sleep <= 0)
    {
        ft_putstr_fd("Error: Time values must be positive\n", 2);
        return(1);
    }
    if (data->nb_must_eat == 0)
    {
        ft_putstr_fd("Error: Number of meals must be positive\n", 2);
        return(1);
    }
    return(0);
}

t_data *parse_args(int ac, char **av)
{
    t_data *data;

    data = malloc(sizeof(t_data));
    if(!data)
        return(NULL);
    memset(data, 0, sizeof(t_data));
    if(check_args(ac, av))
    {
        free(data);
        return(NULL);
    }
    initialise_args(ac, av, data);
    if(data->nb_philo == -2 || data->time_to_die == -2 || data->time_to_eat == -2 || data->time_to_sleep == -2 || data->nb_must_eat == -2)
    {
        ft_putstr_fd("Error: one argument is too big\n", 2);
        free(data);
        return(NULL);
    }
    if(validate_values(data))
    {
        free(data);
        return(NULL);
    }
    return(data);
}
