/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcarranz <fcarranz@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 12:48:56 by fcarranz          #+#    #+#             */
/*   Updated: 2024/09/08 12:41:16 by fcarranz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_philos(t_data *data)
{
	int	i;

	data->philos = (t_philo *)malloc(sizeof(t_philo) * data->nb_philos);
	if (!data->philos)
		return (1);
	i = -1;
	while (++i < data->nb_philos)
	{
		data->philos[i].id = i;
		data->philos[i].status = WAITING_SIMULATION;
		data->philos[i].last_meal = -1;
		data->philos[i].simulation_on = true;
		data->philos[i].fork_left = data->forks + i;
		if (i + 1 == data->nb_philos)
			data->philos[i].fork_right = data->forks;
		else
			data->philos[i].fork_right = data->forks + i + 1;
		if (pthread_mutex_init(&data->philos[i].mtx_dead_check, NULL) == -1)
			return (1);
		data->philos[i].data = data;
	}
	return (0);
}
