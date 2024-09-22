/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep_ml.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcarranz <fcarranz@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 18:17:27 by fcarranz          #+#    #+#             */
/*   Updated: 2024/09/22 13:18:42 by fcarranz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	sleep_ml(long miliseconds)
{
	long	start_time;
	long	elapsed;

	start_time = get_time_ml();
	elapsed = gettmstmp(start_time);
	while (miliseconds > elapsed)
	{
		usleep(200);
		elapsed = gettmstmp(start_time);
	}
}
