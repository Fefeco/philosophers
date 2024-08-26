/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcarranz <fcarranz@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 09:02:08 by fcarranz          #+#    #+#             */
/*   Updated: 2024/08/26 14:06:00 by fcarranz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <limits.h>

// Formatting colours
// # RED	Red text
// # GRN	Green text
// # GRY	Gray text
// # YLW	Yellow text
// # BLU	Blue text
// # MGN	Magenta text
// # CYN	Cyan text
// # WHT	White text
// # RST 	Reset to default
// # CLS	Clear screen
# define RED "\033[31m"
# define GRN "\033[32m"
# define GRY "\033[90m"
# define YLW "\033[33m"
# define BLU "\033[34m"
# define MGN "\033[35m"
# define CYN "\033[36m"
# define WHT "\033[37m"
# define RST "\033[0m"
# define BLD "\033[1m"
# define CLS "\033[2J"
// END Formatting colours

typedef struct s_data
{
	long	nb_philos;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	meals;
}	t_data;

// MAIN
void	parser(t_data *data, char **argv);

//  UTILS
int		ft_strlen(char *str);
void	exit_error(const char *error);

#endif