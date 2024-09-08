/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcarranz <fcarranz@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 12:58:23 by fcarranz          #+#    #+#             */
/*   Updated: 2024/09/08 13:16:50 by fcarranz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	change_status(t_philo *philo, int new_status)
{
	long	timestamp;

	timestamp = gettmstmp(philo->data->start_time);
	philo->status = new_status;
	if (new_status <= DEAD)
		print_status(new_status, philo->id, timestamp);
	if (new_status == EATING)
		philo->last_meal = timestamp;
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

static int	grab_forks(t_philo *philo)
{
	long	start_time;

	start_time = philo->data->start_time;
	if (pthread_mutex_lock(get_first_fork(philo)))
		return (1);
	if (!is_simulation_on(philo))
	{
		if (pthread_mutex_unlock(get_first_fork(philo)))
			return (1);
		return (1);
	}
	printf("%10ld %ld has taken a fork\t🍴\n", gettmstmp(start_time), philo->id);
	if (pthread_mutex_lock(get_second_fork(philo)))
		return (1);
	if (!is_simulation_on(philo))
	{
		drop_forks(philo);
		return (1);
	}
	printf("%10ld %ld has taken a fork\t🍴\n", gettmstmp(start_time), philo->id);
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (is_simulation_on(philo))
	{
		if (philo->id % 2 != 0)
		{
			change_status(philo, THINKING);
			sleep_ml(philo->data->time_to_eat / 2);
		}
		if (!is_simulation_on(philo))
			break ;
		if (grab_forks(philo))
			break ;
		change_status(philo, EATING);
		sleep_ml(philo->data->time_to_eat);
		if (drop_forks(philo))
			break ;
		if (!is_simulation_on(philo))
			break ;
		change_status(philo, SLEPING);
		sleep_ml(philo->data->time_to_sleep);
	}
	return (NULL);
}
