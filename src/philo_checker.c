#include "../include/philo.h"


int	has_starved(t_philo *philo, t_data *data)
{
	long long	current_time;
	int			is_dead;

	current_time = get_time();
	pthread_mutex_lock(&philo->meal_mutex);
	is_dead = (current_time - philo->last_meal > data->time_to_die);
	pthread_mutex_unlock(&philo->meal_mutex);
	if (is_dead)
	{
		pthread_mutex_lock(&data->death_mutex);
		if (!data->someone_died)
		{
			data->someone_died = 1;
			printf("%ldms %2d is dead\n", get_time() - data->start, philo->id);
		}
		pthread_mutex_unlock(&data->death_mutex);
	}
	return (is_dead);
}

int	check_death(t_data *data)
{
	int	check;

	pthread_mutex_lock(&data->death_mutex);
	check = data->someone_died;
	pthread_mutex_unlock(&data->death_mutex);
	return (check);
}

void	*philo_checker(void *checker)
{
	t_data *data;
	int	i;

	i = 0;
	data = (t_data *)checker;
	while (1)
	{
		if (check_death(data))
			return(NULL);
		i = 0;
		while (i < data->nb_philo)
		{
			if (has_starved(&data->philo[i], data))
				return (NULL);
			i++;
		}
		if (count_eat(data, data->philo))
			return (NULL);
		usleep(500);
	}
	return (NULL);
}
