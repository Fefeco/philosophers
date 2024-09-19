/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcarranz <fcarranz@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 12:58:23 by fcarranz          #+#    #+#             */
/*   Updated: 2024/09/19 19:52:29 by fcarranz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	drop_forks(t_philo *philo)
{
	if (pthread_mutex_unlock(get_second_fork(philo)))
		return (1);
	if (pthread_mutex_unlock(get_first_fork(philo)))
		return (1);
	return (0);
}

static int	grab_forks(t_philo *philo)
{
	if (pthread_mutex_lock(get_first_fork(philo)))
		return (1);
	update_and_print_status(GRAB, philo);
	if (get_first_fork(philo) == get_second_fork(philo)
		|| pthread_mutex_lock(get_second_fork(philo)))
	{
		pthread_mutex_unlock(get_first_fork(philo));
		return (1);
	}
	update_and_print_status(GRAB, philo);
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->ate_meals == philo->data->meals)
		update_status(philo, FULL);
	if (philo->id % 2 != 0 && !check_status(philo, FULL))
	{
		update_and_print_status(THINKING, philo);
		sleep_ml(philo->data->time_to_eat / 2);
	}
	while (philo->simulation_on && !check_status(philo, FULL))
	{
		if (grab_forks(philo))
			break ;
		update_and_print_status(EATING, philo);
		if (philo->simulation_on)
			sleep_ml(philo->data->time_to_eat);
		if (drop_forks(philo))
			break ;
		update_and_print_status(SLEEPING, philo);
		if (philo->simulation_on)
			sleep_ml(philo->data->time_to_sleep);
		update_and_print_status(THINKING, philo);
	}
	return (NULL);
}
