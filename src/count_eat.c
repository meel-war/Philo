#include "../include/philo.h"

int	count_eat(t_data *data, t_philo *philo)
{
	int	i;

	if (data->nb_must_eat == -1)
		return (0);
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_lock(&philo[i].meal_mutex);
		if (data->philo[i].meal_eaten == data->nb_must_eat)
		{
			pthread_mutex_lock(&data->full_meal_mutex);
			data->full_meal++;
			pthread_mutex_unlock(&data->full_meal_mutex);
		}
		pthread_mutex_unlock(&philo[i].meal_mutex);
		i++;
	}
	pthread_mutex_lock(&data->full_meal_mutex);
	if (data->full_meal == data->nb_philo)
	{
		pthread_mutex_unlock(&data->full_meal_mutex);
		printf(("Tous les philosophers ont mange %d\n"), data->nb_must_eat);
		return (1);
	}
	pthread_mutex_unlock(&data->full_meal_mutex);
	return (0);
}
