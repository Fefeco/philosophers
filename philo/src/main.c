/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcarranz <fcarranz@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 11:59:38 by fcarranz          #+#    #+#             */
/*   Updated: 2024/09/19 18:43:20 by fcarranz         ###   ########.fr       */
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

static int	init_structs(t_data *data)
{
	if (init_forks(data->nb_philos, &data->forks) == -1)
		return (1);
	if (pthread_mutex_init(&data->mtx_print, NULL) == -1
		|| init_philos(data) == -1)
	{
		destroy_forks(data->nb_philos, &data->forks);
		pthread_mutex_destroy(&data->mtx_print);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
		return (print_help());
	if (parse(&data, argv) || init_structs(&data))
		return (1);
	start_simulation(&data);
	free_philos(&data, data.nb_philos);
	destroy_forks(data.nb_philos, &data.forks);
	pthread_mutex_destroy(&data.mtx_print);
	return (0);
}
