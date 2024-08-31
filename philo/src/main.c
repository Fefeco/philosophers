/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcarranz <fcarranz@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 11:59:38 by fcarranz          #+#    #+#             */
/*   Updated: 2024/08/31 21:29:33 by fcarranz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc == 5 || argc == 6)
	{
		parser(&data, argv);
	}
	else
		exit_error(RED"\t❌  Wrong input  😵\n"RST
			GRY"Usage:\n./philo <number_of_philos> <time_to_die> <time_to_eat>"
			" <time_to_sleep> [number_of_meals]\n"
			BLD"Example:\n./philo 5 800 200 200 9\n"RST);
	return (0);
}
