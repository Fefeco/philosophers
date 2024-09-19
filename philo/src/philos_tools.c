/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcarranz <fcarranz@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 12:48:56 by fcarranz          #+#    #+#             */
/*   Updated: 2024/09/19 18:37:46 by fcarranz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	free_philos(t_data *data, long nb_philos)
{
	long	i;

	i = -1;
	while (++i < nb_philos)
	{
		if (pthread_mutex_destroy(&data->philos[i].mtx_chk_death) == -1)
			break ;
		if (pthread_mutex_destroy(&data->philos[i].mtx_status) == -1)
			break ;
	}
	free (data->philos);
	return (-1);
}

static int	init_philo_mutexes(t_philo *philo)
{
	if (pthread_mutex_init(&philo->mtx_chk_death, NULL) == -1)
		return (1);
	if (pthread_mutex_init(&philo->mtx_status, NULL) == -1)
	{
		pthread_mutex_destroy(&philo->mtx_chk_death);
		return (1);
	}
	return (0);
}

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
		data->philos[i].last_meal = 0;
		data->philos[i].ate_meals = 0;
		data->philos[i].simulation_on = true;
		data->philos[i].mtx_print = &data->mtx_print;
		data->philos[i].fork_left = data->forks + i;
		if (i + 1 == data->nb_philos)
			data->philos[i].fork_right = data->forks;
		else
			data->philos[i].fork_right = data->forks + i + 1;
		if (init_philo_mutexes(&data->philos[i]))
			return (free_philos(data, i));
		data->philos[i].data = data;
	}
	return (0);
}
