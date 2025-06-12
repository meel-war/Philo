/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meel-war <meel-war@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 13:59:26 by meel-war          #+#    #+#             */
/*   Updated: 2025/06/12 18:20:12 by meel-war         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long get_time(void)
{
	struct timeval	current_time;
	long int	time;

	time = 0;
	gettimeofday(&current_time, NULL);
	time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (time);
}

void    philo_sleep(long ms)
{
    long start;
    long passed;

    start = get_time();
    while(1)
    {
        passed = get_time() - start;
        if(passed >= ms)
            break;
        usleep(500);
    } 
}