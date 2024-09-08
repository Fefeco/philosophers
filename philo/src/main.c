/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcarranz <fcarranz@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 11:59:38 by fcarranz          #+#    #+#             */
/*   Updated: 2024/09/08 12:04:21 by fcarranz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	print_help(void)
{
	printf(RED"\v\v\v\t❌  Wrong input  😵\n\v\v"RST);
	printf(GRY"  Usage: ./philo <number_of_philos> <time_to_die> ");
	printf("<time_to_eat> <time_to_sleep> [number_of_meals]\n\v");
	printf(BLD"  Example: ./philo 5 800 200 200 9\n\v"RST);
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
		return (print_help());
	if (parse(&data, argv))
		return (1);
	if (init_structs(&data))
		return (1);
	init_simulation(&data);
	free (data.philos);
	destroy_forks(data.nb_philos, &data.forks);
	return (0);
}
