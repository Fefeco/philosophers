/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcarranz <fcarranz@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 12:58:23 by fcarranz          #+#    #+#             */
/*   Updated: 2024/09/01 14:39:51 by fcarranz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	change_status(t_mutex *mtx_status, int *status, int new_status)
{
	if (pthread_mutex_lock(mtx_status))
		return (1);
	*status = new_status;
	if (pthread_mutex_unlock(mtx_status))
		return (1);
	return (0);
}

static int	grab_forks(t_philo *philo)
{
	t_mutex	*first_fork;
	t_mutex	*second_fork;

	first_fork = philo->fork_right;
	second_fork = philo->fork_left;
	if (philo->id % 2 == 0)
	{
		first_fork = philo->fork_left;
		second_fork = philo->fork_right;
	}
	if (pthread_mutex_lock(first_fork))
		return (1);
	if (pthread_mutex_lock(second_fork))
		return (1);
	return (0);
}

static int	drop_forks(t_philo *philo)
{
	if (pthread_mutex_unlock(philo->fork_left))
		return (1);
	if (pthread_mutex_unlock(philo->fork_right))
		return (1);
	return (0);
}

void	*routine(void *arg)
{
	t_philo	philo;

	philo = *((t_philo *)arg);
	if (pthread_mutex_init(&philo.mtx_status, NULL))
		return (1);
	while (philo.status != DEAD && !philo.end_simulation)
	{
		if (philo.id % 2 == 0)
		{
			if (grab_forks(&philo))
				break ;
			change_status(&philo.mtx_status, &philo.status, EATING);
			sleep_ml(philo.data->time_to_eat);
			if (drop_forks(&philo.mtx_status))
				break ;
			change_status(&philo.mtx_status, &philo.status, SLEPING);
			sleep_ml(philo.data->time_to_sleep);
		}
	}
	if (pthread_mutex_destroy(&philo.mtx_status))
		return (1);
	return (0);
}
