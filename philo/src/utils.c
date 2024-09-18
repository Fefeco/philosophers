/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcarranz <fcarranz@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 12:08:12 by fcarranz          #+#    #+#             */
/*   Updated: 2024/09/12 18:00:56 by fcarranz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	print_status(int status, t_philo *philo)
{
	long	timestamp;

	if (pthread_mutex_lock(philo->mtx_print) == -1
		|| pthread_mutex_lock(&philo->mtx_simulation) == -1)
		return (-1);
	timestamp = gettmstmp(philo->data->start_time);
	if (status == DEAD)
	{
		printf("%ld %ld is dead\n", timestamp, philo->id + 1);
		stop_simulation(philo->data, philo->id);
	}
	else if (status == SLEEPING)
		printf("%ld %ld is sleeping\n", timestamp, philo->id + 1);
	else if (status == EATING)
		printf("%ld %ld is eating\n", timestamp, philo->id + 1);
	else if (status == THINKING)
		printf("%ld %ld is thinking\n", timestamp, philo->id + 1);
	else if (status == GRAB)
		printf("%ld %ld has taken a fork\n", timestamp, philo->id + 1);
	if (pthread_mutex_unlock(&philo->mtx_simulation) == -1
		||pthread_mutex_unlock(philo->mtx_print) == -1)
		return (-1);
	return (timestamp);
}

bool	check_status(t_philo *philo, int status)
{
	bool	ret;

	if (pthread_mutex_lock(&philo->mtx_status) == -1)
		return (false);
	ret = philo->status == status;
	if (pthread_mutex_unlock(&philo->mtx_status) == -1)
		return (false);
	return (ret);
}

bool	is_simulation_on(t_philo *philo)
{
	bool	ret;

	if (pthread_mutex_lock(&philo->mtx_simulation) == -1)
		return (false);
	ret = philo->simulation_on;
	if (pthread_mutex_unlock(&philo->mtx_simulation) == -1)
		return (false);
	return (ret);
}

static int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (*str++)
		++len;
	return (len);
}

int	exit_error(const char *error)
{
	write (2, "\v\v\v", 3);
	write (2, error, ft_strlen((char *)error));
	write (2, "\v\v\v", 3);
	return (1);
}
