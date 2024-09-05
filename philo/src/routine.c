/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcarranz <fcarranz@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 12:58:23 by fcarranz          #+#    #+#             */
/*   Updated: 2024/09/05 22:57:27 by fcarranz         ###   ########.fr       */
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
	if (check_if_all_alive(philo))
		return (1);
	if (pthread_mutex_lock(first_fork))
		return (1);
	printf(YLW"%10ld %ld has taken a fork\n"RST, gettmstmp(philo->data->start_time), philo->id);
	if (check_if_all_alive(philo))
	{
		if (pthread_mutex_unlock(first_fork))
			return (1);
		return (1);
	}
	if (pthread_mutex_lock(second_fork))
		return (1);
	printf(YLW"%10ld %ld has taken a fork\n"RST, gettmstmp(philo->data->start_time), philo->id);
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
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (pthread_mutex_init(&philo->mtx_dead_check, NULL) == -1)
		return (NULL);
	while (philo->all_philos_alive)
	{
		if (philo->id % 2 != 0 && philo->last_meal == -1)
		{
			change_status(philo, THINKING);
			sleep_ml(philo->data->time_to_eat / 2);
		}
		if (check_if_all_alive(philo))
			break ;
		if (grab_forks(philo))
			break ;
		change_status(philo, EATING);
		sleep_ml(philo->data->time_to_eat);
		if (drop_forks(philo))
			break ;
		if (check_if_all_alive(philo))
			break ;
		change_status(philo, SLEPING);
		sleep_ml(philo->data->time_to_sleep);
		if (check_if_all_alive(philo))
			break ;
	}
	if (pthread_mutex_destroy(&philo->mtx_dead_check) == -1)
		return (NULL);
	return (NULL);
}
