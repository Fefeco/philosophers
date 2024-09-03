/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcarranz <fcarranz@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 10:33:21 by fcarranz          #+#    #+#             */
/*   Updated: 2024/09/03 11:21:08 by fcarranz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int init_simulation(t_data *data)
{
	struct timeval	start;
	int				i;

	if (gettimeofday(&start, NULL) == -1)
		return (-1);
	data->start_time = (start.tv_sec * 1000) + (start.tv_usec / 1000);
	i = -1;
	while (++i < data->nb_philos)
		pthread_create(&data->philos[i].thread, NULL, routine, &data->philos[i]);
	i = -1;
	while (++i < data->nb_philos)
		pthread_join(data->philos[i].thread, NULL);
	return (0);
}