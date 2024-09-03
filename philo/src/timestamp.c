/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timestamp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcarranz <fcarranz@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 09:56:59 by fcarranz          #+#    #+#             */
/*   Updated: 2024/09/02 10:36:25 by fcarranz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	gettmstmp(long start)
{
	struct timeval	current;
	long			stop;

	if (gettimeofday(&current, NULL) == -1)
		return (-1);
	stop = ((current.tv_sec * 1000) + (current.tv_usec / 1000));
	return (stop - start);
}