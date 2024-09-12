/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcarranz <fcarranz@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 12:58:23 by fcarranz          #+#    #+#             */
/*   Updated: 2024/09/12 11:59:24 by fcarranz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	change_status(t_philo *philo, int new_status)
{
	long	timestamp;
	long	start_time;

	start_time = philo->data->start_time;
	if (pthread_mutex_lock(&philo->mtx_status) == -1)
		return (1);
	if (philo->status != DEAD && philo->status != FULL)
	{
		philo->status = new_status;
		if (new_status == SLEEPING && philo->ate_meals == philo->data->meals)
			philo->status = FULL;
		if (new_status <= THINKING && philo->status != FULL)
			timestamp = print_status(new_status, philo->id, start_time);
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

static int	grab_forks(t_philo *philo, long start_time)
{
	long	id;

	id = philo->id + 1;
	if (pthread_mutex_lock(get_first_fork(philo)))
		return (1);
	if (is_simulation_on(philo))
		printf("%ld %ld has taken a fork\n", gettmstmp(start_time), id);
	else
	{
		pthread_mutex_unlock(get_first_fork(philo));
		return (1);
	}
	if (get_first_fork(philo) == get_second_fork(philo)
		|| pthread_mutex_lock(get_second_fork(philo)))
		return (1);
	if (is_simulation_on(philo))
	{
		printf("%ld %ld has taken a fork\n", gettmstmp(start_time), id);
		return (0);
	}
	drop_forks(philo);
	return (1);
}

static int	check_meals(t_philo	*philo)
{
	int	ret;

	ret = 0;
	if (pthread_mutex_lock(&philo->mtx_status) == -1)
		return (1);
	if (philo->status == FULL)
		ret = 1;
	if (pthread_mutex_unlock(&philo->mtx_status) == -1)
		return (1);
	return (ret);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 != 0)
	{
		change_status(philo, THINKING);
		sleep_ml(philo->data->time_to_eat / 2);
	}
	while (is_simulation_on(philo) && !check_meals(philo))
	{
		if (grab_forks(philo, philo->data->start_time))
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
