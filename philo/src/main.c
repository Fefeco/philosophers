/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcarranz <fcarranz@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 11:59:38 by fcarranz          #+#    #+#             */
/*   Updated: 2024/08/31 21:10:14 by fcarranz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_data	data;
	long	request_time;
	struct timeval	start_time;
	struct timeval	end_time;
	struct timeval	start_time2;
	struct timeval	end_time2;


	if (argc == 5 || argc == 6)
	{
		parser(&data, argv);
		request_time = data.time_to_eat;
		gettimeofday(&start_time, NULL);
		usleep(request_time * 1000);
		gettimeofday(&end_time, NULL);
		printf("tv_sec: %ld\ntv_usec: %ld\nTotal: %ld\n", (start_time.tv_sec * 1000), (start_time.tv_usec / 1000), (start_time.tv_sec * 1000) + (start_time.tv_usec / 1000));
		long start = (start_time.tv_sec * 1000) + (start_time.tv_usec / 1000);
		long end = (end_time.tv_sec * 1000) + (end_time.tv_usec / 1000);
		long dif = end - start;
		printf("========\nDifrences of time\n========\n-usleep\nstr: %ld\nend: %ld\nTotal: %ld\n", start, end, dif);
		gettimeofday(&start_time2, NULL);
		sleep_ml(request_time);
		gettimeofday(&end_time2, NULL);
		long start2 = (start_time2.tv_sec * 1000) + (start_time2.tv_usec / 1000);
		long end2 = (end_time2.tv_sec * 1000) + (end_time2.tv_usec / 1000);
		long dif2 = end2 - start2;
		printf("-sleep_ml\nstr: %ld\nend: %ld\nTotal: %ld\n========\n", start2, end2, dif2);
	}
	else
		exit_error(RED"\t❌  Wrong input  😵\n"RST
			GRY"Usage:\n./philo <number_of_philos> <time_to_die> <time_to_eat>"
			" <time_to_sleep> [number_of_meals]\n"
			BLD"Example:\n./philo 5 800 200 200 9\n"RST);
	return (0);
}
