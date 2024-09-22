/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcarranz <fcarranz@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 10:33:21 by fcarranz          #+#    #+#             */
/*   Updated: 2024/09/22 13:16:22 by fcarranz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool	is_philo_dead(t_philo *philo, long start_time)
{
	long	elapsed_time;
	long	timestamp;

	if (philo->status == FULL)
		return (false);
	timestamp = gettmstmp(start_time);
	elapsed_time = timestamp - philo->last_meal;
	if (elapsed_time > philo->data->time_to_die)
		return (true);
	return (false);
}

static void	check_philos(t_data *data)
{
	long	i;
	long	philos_full;

	i = -1;
	philos_full = 0;
	while (philos_full != data->nb_philos && !data->stop_simulation)
	{
		if (++i == data->nb_philos)
		{
			i = 0;
			philos_full = 0;
		}
		if (pthread_mutex_lock(&data->philos[i].mtx_chk_death))
			return ;
		if (is_philo_dead(&data->philos[i], data->start_time))
			data->stop_simulation = true;
		else if (data->philos[i].status == FULL)
			++philos_full;
		if (pthread_mutex_unlock(&data->philos[i].mtx_chk_death))
			return ;
	}
	if (data->stop_simulation)
		update_and_print_status(DEAD, &data->philos[i]);
}

void	start_simulation(t_data *data)
{
	long	i;

	data->start_time = get_time_ml();
	data->stop_simulation = false;
	i = -1;
	while (++i < data->nb_philos)
		pthread_create(&data->philos[i].th, NULL, routine, &data->philos[i]);
	check_philos(data);
	i = -1;
	while (++i < data->nb_philos)
		pthread_join(data->philos[i].th, NULL);
}
