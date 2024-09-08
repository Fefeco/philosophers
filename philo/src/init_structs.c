/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcarranz <fcarranz@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 09:56:17 by fcarranz          #+#    #+#             */
/*   Updated: 2024/09/08 12:03:33 by fcarranz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_structs(t_data *data)
{
	if (init_forks(data->nb_philos, &data->forks) == -1)
		return (1);
	if (init_philos(data) == -1)
		return (1);
	return (0);
}
