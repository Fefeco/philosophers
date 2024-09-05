/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcarranz <fcarranz@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 10:33:21 by fcarranz          #+#    #+#             */
/*   Updated: 2024/09/05 23:29:06 by fcarranz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	check_philos(t_data *data)
{
	long	i;
	long	timestamp;

	i = 0;
	while (1)
	{
		if (!i)
			timestamp = gettmstmp(data->start_time);
		if (check_dead(data->philos + i, timestamp))
		{
			i = -1;
			while (++i < data->nb_philos)
				if (pthread_mutex_lock(&data->philos[i].mtx_dead_check) == -1)
					break ;
			i = -1;
			while (++i < data->nb_philos)
				data->philos[i].all_philos_alive = false;
			i = -1;
			while (++i < data->nb_philos)
				if (pthread_mutex_unlock(&data->philos[i].mtx_dead_check) == -1)
					break ;
			break ;
		}
		++i;
		if (i == data->nb_philos)
		{
			i = 0;
			usleep(500);
		}
	}
}

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
	check_philos(data);
	i = -1;
	while (++i < data->nb_philos)
		pthread_join(data->philos[i].thread, NULL);
	return (0);
}