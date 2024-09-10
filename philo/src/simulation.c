/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcarranz <fcarranz@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 10:33:21 by fcarranz          #+#    #+#             */
/*   Updated: 2024/09/10 11:33:55 by fcarranz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	stop_simulation(t_data *data)
{
	long	i;

	i = -1;
	while (++i < data->nb_philos)
		if (pthread_mutex_lock(&data->philos[i].mtx_simulation) == -1)
			return ;
	i = -1;
	while (++i < data->nb_philos)
		data->philos[i].simulation_on = false;
	i = -1;
	while (++i < data->nb_philos)
		if (pthread_mutex_unlock(&data->philos[i].mtx_simulation) == -1)
			return ;
}

static bool	is_philo_dead(t_philo *philo, long timestamp)
{
	long	elapsed_time;
	bool	exit;

	exit = false;
	elapsed_time = timestamp - philo->last_meal;
	if (elapsed_time > philo->data->time_to_die && philo->status != FULL)
	{
		philo->status = DEAD;
		print_status(DEAD, philo->id, timestamp);
		stop_simulation(philo->data);
		exit = true;
	}
	if (exit)
		return (true);
	return (false);
}

static void	check_philos(t_data *data)
{
	long	i;
	long	philos_full;
	long	timestamp;

	i = 0;
	while (1)
	{
		if (i == 0)
		{
			timestamp = gettmstmp(data->start_time);
			philos_full = 0;
		}
		if (pthread_mutex_lock(&data->philos[i].mtx_status))
			return ;
		if (is_philo_dead(&data->philos[i], timestamp))
			break ;
		if (data->philos[i].status == FULL)
			++philos_full;
		if (pthread_mutex_unlock(&data->philos[i].mtx_status))
			return ;
		if (++i == data->nb_philos)
		{
			if (philos_full == data->nb_philos)
				break ;
			i = 0;
			usleep(500);
		}
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
