/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meel-war <meel-war@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:39:54 by meel-war          #+#    #+#             */
/*   Updated: 2025/06/12 18:04:47 by meel-war         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	print_status(t_data *data, t_philo *philo, char *status)
{
	long	curent_time;

	pthread_mutex_lock(&data->print_mutex);
	curent_time = get_time() - data->start;
	pthread_mutex_lock(&data->death_mutex);
	if (!data->someone_died)
	{
		printf("/%ld/ %d %s", curent_time, philo->id, status);
	}
	pthread_mutex_unlock(&data->death_mutex);
	pthread_mutex_unlock(&data->print_mutex);
}
