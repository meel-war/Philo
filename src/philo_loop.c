/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meel-war <meel-war@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 13:59:20 by meel-war          #+#    #+#             */
/*   Updated: 2025/06/12 18:30:44 by meel-war         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	take_forks(t_data *data, t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&data->forks[philo->left]);
		print_status(data, philo, "take left fork\n");
		pthread_mutex_lock(&data->forks[philo->right]);
		print_status(data, philo, "take right fork\n");
	}
	else
	{
		pthread_mutex_lock(&data->forks[philo->right]);
		print_status(data, philo, "take right fork\n");
		pthread_mutex_lock(&data->forks[philo->left]);
		print_status(data, philo, "take left fork\n");
	}
}

void	eating(t_data *data, t_philo *philo)
{
	print_status(data, philo, "is eating\n");
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = get_time();
	philo->meal_eaten++;
	pthread_mutex_unlock(&philo->meal_mutex);
	philo_sleep(data->time_to_eat);
}

void	*philo_loop(void *arg)
{
	t_philo	*phi;
	t_data	*data;

	phi = (t_philo *)arg;
	data = phi->data;
	while (1)
	{
		pthread_mutex_lock(&data->death_mutex);
		if (data->someone_died)
		{
			pthread_mutex_unlock(&data->death_mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&data->death_mutex);
		print_status(data, phi, "is thinking\n");
		take_forks(data, phi);
		eating(data, phi);
		pthread_mutex_unlock(&data->forks[phi->left]);
		pthread_mutex_unlock(&data->forks[phi->right]);
		print_status(data, phi, "is sleeping\n");
		philo_sleep(data->time_to_sleep);
		usleep(500);
	}
	return (NULL);
}






