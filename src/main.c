/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meel-war <meel-war@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 13:59:16 by meel-war          #+#    #+#             */
/*   Updated: 2025/06/12 13:59:17 by meel-war         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int ac, char **av)
{
	t_data	*data;

	data = parse_args(ac, av);
	if (!data)
		return (1);
	if (initiate_philo(data) != 0)
		return (1);
	if (link_thread(data))
		return (1);
	free_all(data);
	return (0);
}
