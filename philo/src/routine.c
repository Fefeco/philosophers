/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcarranz <fcarranz@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 12:58:23 by fcarranz          #+#    #+#             */
/*   Updated: 2024/09/12 18:02:27 by fcarranz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// int	print_statement()

static int	change_status(t_philo *philo, int new_status)
{
	long	timestamp;

	if (pthread_mutex_lock(&philo->mtx_status) == -1)
		return (1);
	if (philo->status != DEAD && philo->status != FULL)
	{
		philo->status = new_status;
		if (new_status == SLEEPING && philo->ate_meals == philo->data->meals)
			philo->status = FULL;
		if (new_status <= THINKING && philo->status != FULL)
			timestamp = print_status(new_status, philo);
		if (new_status == EATING)
		{
			philo->last_meal = timestamp;
			++philo->ate_meals;
		}
	}
	if (pthread_mutex_unlock(&philo->mtx_status) == -1)
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

static int	grab_forks(t_philo *philo)
{
	if (pthread_mutex_lock(get_first_fork(philo)))
		return (1);
	if (get_first_fork(philo) != get_second_fork(philo))
		print_status(GRAB, philo);
	else
	{
		pthread_mutex_unlock(get_first_fork(philo));
		return (1);
	}
	if (pthread_mutex_lock(get_second_fork(philo)))
		return (1);
	if (print_status(GRAB, philo) > 0)
		return (0);
	drop_forks(philo);
	return (1);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->ate_meals == philo->data->meals)
		change_status(philo, FULL);
	if (philo->id % 2 != 0)
	{
		change_status(philo, THINKING);
		sleep_ml(philo->data->time_to_eat / 2);
	}
	while (is_simulation_on(philo) && !check_status(philo, FULL))
	{
		if (grab_forks(philo))
			break ;
		change_status(philo, EATING);
		sleep_ml(philo->data->time_to_eat);
		if (drop_forks(philo) || !is_simulation_on(philo))
			break ;
		change_status(philo, SLEEPING);
		sleep_ml(philo->data->time_to_sleep);
		if (is_simulation_on(philo))
			change_status(philo, THINKING);
	}
	return (NULL);
}
