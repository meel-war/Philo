/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meel-war <meel-war@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 13:59:23 by meel-war          #+#    #+#             */
/*   Updated: 2025/06/12 16:56:20 by meel-war         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	free_all(t_data *data)
{
	int	i;

	i = 0;
	if (data)
	{
		if (data->forks)
		{
			while (i < data->nb_philo)
			{
				pthread_mutex_destroy(&data->forks[i]);
				i++;
			}
			free(data->forks);
		}
		i = 0;
		if (data->philo)
		{
			while (i < data->nb_philo)
			{
				pthread_mutex_destroy(&data->philo[i].meal_mutex);
				i++;
			}
			free(data->philo);
		}
		pthread_mutex_destroy(&data->death_mutex);
		pthread_mutex_destroy(&data->full_meal_mutex);
        pthread_mutex_destroy(&data->print_mutex);
		pthread_mutex_destroy(&data->dprint_mutex);
		free(data);
	}
}
