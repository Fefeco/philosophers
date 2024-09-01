/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcarranz <fcarranz@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 12:48:56 by fcarranz          #+#    #+#             */
/*   Updated: 2024/09/01 14:36:37 by fcarranz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_philos(t_data *data)
{
	int	i;

	data->philos = (t_philo *)malloc(sizeof(t_philo) * data->nb_philos);
	if (!data->philos)
		return (1);
	i = 0;
	while (i < data->nb_philos)
	{
		data->philos[i].status = WAITING_SIMULATION;
		data->philos[i].id = i;
		data->philos[i].fork_left = &data->forks[i];
		if (i + 1 == data->nb_philos)
			data->philos[i].fork_right = &data->forks[0];
		else
			data->philos[i].fork_right = &data->forks[i + 1];
		data->philos[i].end_simulation = false;
		++i;
	}
	return (0);
}
