/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meel-war <meel-war@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 13:59:13 by meel-war          #+#    #+#             */
/*   Updated: 2025/06/12 17:19:38 by meel-war         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	join_thread(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_join(data->philo[i].thread, NULL) != 0)
			return (1);
		i++;
	}
	pthread_join(data->checker_thread, NULL);
	return (0);
}

int	link_thread(t_data *data)
{
	int	i;

	i = 0;
	data->start = get_time();
	while (i < data->nb_philo)
	{
		data->philo[i].last_meal = data->start;
		if (pthread_create(&data->philo[i].thread, NULL, philo_loop,
				(void *)&data->philo[i]) != 0)
		{
			free_all(data);
			return (1);
		}
		i++;
	}
	if (pthread_create(&data->checker_thread, NULL, philo_checker,
			(void *)data) != 0)
	{
		free_all(data);
		return (1);
	}
	if (join_thread(data) != 0)
	{
		free_all(data);
		return (1);
	}
	return (0);
}
