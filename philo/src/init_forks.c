/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_forks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcarranz <fcarranz@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 21:49:10 by fcarranz          #+#    #+#             */
/*   Updated: 2024/09/01 12:06:19 by fcarranz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_forks(int total_forks, t_mutex **forks)
{
	t_mutex	*forks_tmp;
	int		i;

	forks_tmp = (t_mutex *)malloc(sizeof(t_mutex) * total_forks);
	if (!forks_tmp)
		return (1);
	i = 0;
	while (i < total_forks)
	{
		if (pthread_mutex_init(forks_tmp + i, NULL))
			break ;
		++i;
	}
	if (i != total_forks)
	{
		printf("Error creating forks\n");
		while (i != 0)
		{
			pthread_mutex_destroy(forks_tmp + i);
			--i;
		}
		return (-1);
	}
	(*forks) = forks_tmp;
	return (0);
}
