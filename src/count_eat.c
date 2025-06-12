/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meel-war <meel-war@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 13:58:36 by meel-war          #+#    #+#             */
/*   Updated: 2025/06/12 18:26:39 by meel-war         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		printf(("Tous les philosophers ont mange %dx\n"), data->nb_must_eat);
		pthread_mutex_lock(&data->death_mutex);
		data->someone_died = 1;
		pthread_mutex_unlock(&data->death_mutex);
		return (1);
	}
	pthread_mutex_unlock(&data->full_meal_mutex);
	return (0);
}
