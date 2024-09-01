/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep_ml.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcarranz <fcarranz@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 18:17:27 by fcarranz          #+#    #+#             */
/*   Updated: 2024/09/01 11:42:40 by fcarranz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	sleep_ml(long miliseconds)
{
	struct timeval	start;
	struct timeval	current;
	long			start_time;
	long			end_time;

	if (gettimeofday(&start, NULL) == -1)
		return (-1);
	start_time = ((start.tv_sec * 1000) + (start.tv_usec / 1000));
	end_time = start_time;
	while (miliseconds != (end_time - start_time))
	{
		if (gettimeofday(&current, NULL) == -1)
			return (-1);
		end_time = ((current.tv_sec * 1000) + (current.tv_usec / 1000));
		usleep(11);
	}
	return (0);
}
