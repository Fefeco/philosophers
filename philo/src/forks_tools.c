/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcarranz <fcarranz@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 21:49:10 by fcarranz          #+#    #+#             */
/*   Updated: 2024/09/10 13:36:12 by fcarranz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_mutex	*get_first_fork(t_philo *philo)
{
	if (philo->id % 2 != 0)
		return (philo->fork_left);
	return (philo->fork_right);
}

t_mutex	*get_second_fork(t_philo *philo)
{
	if (philo->id % 2 != 0)
		return (philo->fork_right);
	return (philo->fork_left);
}

void	destroy_forks(int total_forks, t_mutex **forks)
{
	int	i;

	i = -1;
	while (++i != total_forks)
		pthread_mutex_destroy(*forks + i);
	free (*forks);
	*forks = NULL;
}

int	init_forks(int total_forks, t_mutex **forks)
{
	int	i;

	*forks = (t_mutex *)malloc(sizeof(t_mutex) * total_forks);
	if (!(*forks))
		return (1);
	i = -1;
	while (++i < total_forks)
		if (pthread_mutex_init((*forks) + i, NULL))
			break ;
	if (i != total_forks)
	{
		printf(RED"Error creating forks\n"RST);
		destroy_forks(i, forks);
		return (-1);
	}
	return (0);
}
