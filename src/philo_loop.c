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
	if (is_dead)
	{
		pthread_mutex_lock(&data->death_mutex);
		if (!data->someone_died)
		{
			data->someone_died = 1;
			pthread_mutex_unlock(&data->death_mutex);
			print_status(data, philo, "%d is dead\n");;
		}
		pthread_mutex_unlock(&data->death_mutex);
	}
	return (is_dead);
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
			break ;
		i = 0;
		while (i < data->nb_philo)
		{
			if (has_starved(&data->philo[i], data))
				return (NULL);
			i++;
		}
		if (count_eat(data, data->philo))
			return (NULL);
		usleep(5000);
	}
	return (NULL);
}
