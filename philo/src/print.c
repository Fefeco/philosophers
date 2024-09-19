/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcarranz <fcarranz@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 18:17:23 by fcarranz          #+#    #+#             */
/*   Updated: 2024/09/19 20:39:41 by fcarranz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool	is_safe_print(t_philo *philo, long timestamp)
{
	if (philo->status == FULL)
		return (false);
	return ((timestamp - philo->last_meal) <= philo->data->time_to_die);
}

static void	print_status(int new_status, t_philo *philo, long timestamp)
{
	if (new_status == DEAD)
		printf(RED"%ld %ld is dead\n"RST, timestamp, philo->id + 1);
	else if (new_status == SLEEPING)
		printf("%ld %ld is sleeping\n", timestamp, philo->id + 1);
	else if (new_status == EATING)
		printf(GRN"%ld %ld is eating\n"RST, timestamp, philo->id + 1);
	else if (new_status == THINKING)
		printf(GRY"%ld %ld is thinking\n"RST, timestamp, philo->id + 1);
	else if (new_status == GRAB)
		printf(BLU"%ld %ld has taken a fork\n"RST, timestamp, philo->id + 1);
}

void	update_and_print_status(int new_status, t_philo *philo)
{
	long	timestamp;

	if (pthread_mutex_lock(&philo->mtx_chk_death) == -1)
		return ;
	if (pthread_mutex_lock(philo->mtx_print) == -1)
		return ;
	timestamp = gettmstmp(philo->data->start_time);
	if (philo->data->stop_simulation && new_status != DEAD)
		philo->simulation_on = false;
	else if (is_safe_print(philo, timestamp) || new_status == DEAD)
	{
		print_status(new_status, philo, timestamp);
		if (new_status == EATING)
		{
			philo->last_meal = timestamp;
			++philo->ate_meals;
		}
		update_status(philo, new_status);
	}
	if (pthread_mutex_unlock(philo->mtx_print) == -1)
		return ;
	if (pthread_mutex_unlock(&philo->mtx_chk_death) == -1)
		return ;
}
