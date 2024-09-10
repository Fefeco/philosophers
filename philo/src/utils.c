/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcarranz <fcarranz@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 12:08:12 by fcarranz          #+#    #+#             */
/*   Updated: 2024/09/10 16:14:43 by fcarranz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_status(int status, long id, long timestamp)
{
	if (status == DEAD)
		printf("%ld %ld is dead\n", timestamp, id);
	else if (status == SLEEPING)
		printf("%ld %ld is sleeping\n", timestamp, id);
	else if (status == EATING)
		printf("%ld %ld is eating\n", timestamp, id);
	else if (status == THINKING)
		printf("%ld %ld is thinking\n", timestamp, id);
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
