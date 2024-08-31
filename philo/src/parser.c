/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcarranz <fcarranz@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 12:55:59 by fcarranz          #+#    #+#             */
/*   Updated: 2024/08/31 21:15:05 by fcarranz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool	is_number(char c)
{
	return (c >= '0' && c <= '9');
}

static bool	is_space(char c)
{
	return ((c >= '\t' && c <= '\r') || c == ' ');
}

static char	*check_values(char *str)
{
	if (!str || !*str)
		exit_error("Wrong value. Null is not a value\n");
	while (is_space(*str))
		++str;
	if (*str == '+')
		++str;
	if (*str == '-')
		exit_error("Wrong value. Negative numbers are no valid\n");
	if (!is_number(*str))
		exit_error("Wrong value\n");
	return (str);
}

static long	ft_atol(char *str)
{
	long	number;

	number = 0;
	str = check_values(str);
	while (is_number(*str))
	{
		number = (number * 10) + ((*str++) - '0');
		if (number > INT_MAX)
			exit_error("Wrong value. Value is grater than INT_MAX\n");
	}
	return (number);
}

void	parser(t_data *data, char **argv)
{
	data->nb_philos = ft_atol(argv[1]);
	data->time_to_die = ft_atol(argv[2]);
	data->time_to_eat = ft_atol(argv[3]);
	data->time_to_sleep = ft_atol(argv[4]);
	if (argv[5])
		data->meals = ft_atol(argv[5]);
	else
		data->meals = -1;
}
