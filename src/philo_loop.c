#include "../include/philo.h"

void	take_forks(t_data *data, t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&data->forks[philo->left]);
		printf("Philosophe %d prend la fourchette gauche\n", philo->id);
		pthread_mutex_lock(&data->forks[philo->right]);
		printf("Philosophe %d prend la fourchette droite\n", philo->id);
	}
	else
	{
		pthread_mutex_lock(&data->forks[philo->right]);
		printf("Philosophe %d prend la fourchette droite\n", philo->id);
		pthread_mutex_lock(&data->forks[philo->left]);
		printf("Philosophe %d prend la fourchette gauche\n", philo->id);
	}
}

void	eating(t_data *data, t_philo *philo)
{
	printf("Philosophe %d mange\n", philo->id);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = get_time();
	philo->meal_eaten++;
	pthread_mutex_unlock(&philo->meal_mutex);
	usleep(data->time_to_eat * 1000);
}

void	*philo_loop(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	while (1)
	{
		pthread_mutex_lock(&data->death_mutex);
		if (data->someone_died)
		{
			pthread_mutex_unlock(&data->death_mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&data->death_mutex);
		printf("Philosophe %d pense\n", philo->id);
		take_forks(data, philo);
		eating(data, philo), pthread_mutex_unlock(&data->forks[philo->left]);
		pthread_mutex_unlock(&data->forks[philo->right]);
		printf("Philosophe %d dort\n", philo->id);
		usleep(data->time_to_sleep * 1000);
	}
	return (NULL);
}
int	check_death(t_data *data)
{
	int	check;

	pthread_mutex_lock(&data->death_mutex);
	check = data->someone_died;
	pthread_mutex_unlock(&data->death_mutex);
	return (check);
}

int	has_starved(t_philo *philo, t_data *data)
{
	long long	current_time;
	int			is_dead;

    current_time = get_time();
    pthread_mutex_lock(&philo->meal_mutex);
    is_dead = (current_time - philo->last_meal > data->time_to_die);
    pthread_mutex_unlock(&philo->meal_mutex);
    if(is_dead)
    {
        pthread_mutex_lock(&data->death_mutex);
        if(!data->someone_died)
        {
            data->someone_died = 1;
            pthread_mutex_unlock(&data->death_mutex);
            printf("Un Philosophe est mort\n");
        }
        pthread_mutex_unlock(&data->death_mutex);
    }
    return(is_dead);
}

void	*philo_checker(void *checker)
{
	t_philo *philo;
	t_data *data;
	int i;

	philo = (t_philo *)checker;
	data = philo->data;
	while (1)
	{
		if (check_death(data))
			break ;
		i = 0;
		while (i < data->nb_philo)
		{
			if(has_starved(&philo[i], data))
                return(NULL);
			i++;
		}
		if (count_eat(data, philo))
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}