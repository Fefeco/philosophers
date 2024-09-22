/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcarranz <fcarranz@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 12:08:12 by fcarranz          #+#    #+#             */
/*   Updated: 2024/09/22 13:19:17 by fcarranz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	get_time_ml(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (-1);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	update_status(t_philo *philo, int new_status)
{
	if (pthread_mutex_lock(&philo->mtx_status) == -1)
		return (1);
	if (philo->status != DEAD && philo->status != FULL)
	{
		philo->status = new_status;
		if (philo->ate_meals == philo->data->meals)
			philo->status = FULL;
	}
	if (pthread_mutex_unlock(&philo->mtx_status) == -1)
		return (1);
	return (0);
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
