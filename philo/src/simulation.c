/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcarranz <fcarranz@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 10:33:21 by fcarranz          #+#    #+#             */
/*   Updated: 2024/09/12 14:22:03 by fcarranz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	stop_simulation(t_data *data, long philo_id)
{
	long	i;

	i = -1;
	while (++i < data->nb_philos)
	{
		if (i == philo_id)
			continue ;
		if (pthread_mutex_lock(&data->philos[i].mtx_simulation) == -1)
			return ;
	}
	i = -1;
	while (++i < data->nb_philos)
		data->philos[i].simulation_on = false;
	i = -1;
	while (++i < data->nb_philos)
	{
		if (i == philo_id)
			continue ;
		if (pthread_mutex_unlock(&data->philos[i].mtx_simulation) == -1)
			return ;
	}
}

static bool	is_philo_dead(t_philo *philo, long start_time)
{
	long	elapsed_time;
	long	timestamp;
	bool	exit;

	exit = false;
	timestamp = gettmstmp(start_time);
	elapsed_time = timestamp - philo->last_meal;
	if (philo->status != FULL && elapsed_time > philo->data->time_to_die)
	{
		philo->status = DEAD;
		print_status(DEAD, philo);
		exit = true;
	}
	return (exit);
}

static void	check_philos(t_data *data)
{
	long	i;
	long	philos_full;

	i = -1;
	philos_full = 0;
	while (philos_full != data->nb_philos)
	{
		if (++i == data->nb_philos)
		{
			usleep(500);
			i = 0;
			philos_full = 0;
		}
		if (pthread_mutex_lock(&data->philos[i].mtx_status))
			return ;
		if (is_philo_dead(&data->philos[i], data->start_time))
		{
			pthread_mutex_unlock(&data->philos[i].mtx_status);
			break ;
		}
		if (data->philos[i].status == FULL)
			++philos_full;
		if (pthread_mutex_unlock(&data->philos[i].mtx_status))
			return ;
	}
}

void	start_simulation(t_data *data)
{
	struct timeval	start;
	int				i;

	if (gettimeofday(&start, NULL) == -1)
		return ;
	data->start_time = (start.tv_sec * 1000) + (start.tv_usec / 1000);
	i = -1;
	while (++i < data->nb_philos)
		pthread_create(&data->philos[i].th, NULL, routine, &data->philos[i]);
	check_philos(data);
	i = -1;
	while (++i < data->nb_philos)
		pthread_join(data->philos[i].th, NULL);
}
