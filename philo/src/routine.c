/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcarranz <fcarranz@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 12:58:23 by fcarranz          #+#    #+#             */
/*   Updated: 2024/09/03 14:34:43 by fcarranz         ###   ########.fr       */
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
	if (philo->id % 2 != 0)
	{
		first_fork = philo->fork_left;
		second_fork = philo->fork_right;
	}
	if (pthread_mutex_lock(first_fork))
		return (1);
	// printf("%ld %ld has taken a fork\n", gettmstmp(philo->data->start_time), philo->id);
	printf("%10ld %ld has taken the first fork: %p\n", gettmstmp(philo->data->start_time), philo->id, first_fork);
	if (pthread_mutex_lock(second_fork))
		return (1);
	// printf("%ld %ld has taken a fork\n", gettmstmp(philo->data->start_time), philo->id);
	printf("%10ld %ld has taken the second fork: %p\n", gettmstmp(philo->data->start_time), philo->id, second_fork);
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
	long	timestamp;

	philo = *((t_philo *)arg);
	if (pthread_mutex_init(&philo.mtx_status, NULL))
		return (NULL);
	while (philo.status != DEAD && !philo.end_simulation)
	{
		timestamp = gettmstmp(philo.data->start_time);
		if (timestamp > philo.data->time_to_die)
			printf("%10ld %ld is dead\t😵\n", timestamp, philo.id);
		if (grab_forks(&philo))
			break ;
		change_status(&philo.mtx_status, &philo.status, EATING);
		printf("%10ld %ld is eating\n", gettmstmp(philo.data->start_time), philo.id);
		sleep_ml(philo.data->time_to_eat);
		if (drop_forks(&philo))
			break ;
		printf("%10ld %ld is sleeping\n", gettmstmp(philo.data->start_time), philo.id);
		change_status(&philo.mtx_status, &philo.status, SLEPING);
		sleep_ml(philo.data->time_to_sleep);
		printf("%10ld %ld is thinking\n", gettmstmp(philo.data->start_time), philo.id);
	}
	pthread_mutex_destroy(&philo.mtx_status);
	return (NULL);
}
