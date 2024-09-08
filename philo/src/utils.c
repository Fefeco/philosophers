/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcarranz <fcarranz@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 12:08:12 by fcarranz          #+#    #+#             */
/*   Updated: 2024/09/08 12:43:15 by fcarranz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_status(int status, long id, long timestamp)
{
	if (status == DEAD)
		printf(RED"%10ld %ld is dead\t\t😵\n"RST, timestamp, id);
	else if (status == SLEPING)
		printf("%10ld %ld is sleeping\t😴\n", timestamp, id);
	else if (status == EATING)
		printf("%10ld %ld is eating\t\t🍝\n", timestamp, id);
	else if (status == THINKING)
		printf("%10ld %ld is thinking\t🤔\n", timestamp, id);
}

bool	is_simulation_on(t_philo *philo)
{
	bool	ret;

	if (pthread_mutex_lock(&philo->mtx_dead_check) == -1)
		return (false);
	ret = philo->simulation_on;
	if (pthread_mutex_unlock(&philo->mtx_dead_check) == -1)
		return (false);
	return (ret);
}

int	check_dead(t_philo *philo, long timestamp)
{
	long	elapsed_time;

	if (philo->last_meal == -1)
		elapsed_time = timestamp;
	else
		elapsed_time = timestamp - philo->last_meal;
	if (elapsed_time > philo->data->time_to_die)
	{
		change_status(philo, DEAD);
		return (1);
	}
	return (0);
}

int	ft_strlen(char *str)
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
