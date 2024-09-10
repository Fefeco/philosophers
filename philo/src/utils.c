/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcarranz <fcarranz@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 12:08:12 by fcarranz          #+#    #+#             */
/*   Updated: 2024/09/10 14:18:26 by fcarranz         ###   ########.fr       */
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
