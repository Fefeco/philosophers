/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcarranz <fcarranz@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 09:02:08 by fcarranz          #+#    #+#             */
/*   Updated: 2024/09/12 17:59:49 by fcarranz         ###   ########.fr       */
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
# include <sys/time.h>

// Formatting colours
// # RED	Red text
// # GRY	Gray text
// # BLD	Bold text
// # RST 	Reset to default
# define RED "\033[1;31m"
# define GRY "\033[90m"
# define BLD "\033[1m"
# define RST "\033[0m"
// END Formatting colours

typedef pthread_mutex_t	t_mutex;
typedef pthread_t		t_thd;
typedef struct s_data	t_data;
typedef struct s_philo	t_philo;
typedef enum e_status	t_status;

enum e_status
{
	SLEEPING,
	EATING,
	THINKING,
	FULL,
	DEAD,
	GRAB,
	WAITING_SIMULATION
};

struct s_philo
{
	long	id;
	int		status;
	long	last_meal;
	long	ate_meals;
	bool	simulation_on;
	t_thd	th;
	t_mutex	*mtx_print;
	t_mutex	*fork_left;
	t_mutex	*fork_right;
	t_mutex	mtx_simulation;
	t_mutex	mtx_status;
	t_data	*data;
};

struct s_data
{
	long	nb_philos;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	meals;
	long	start_time;
	t_mutex	*forks;
	t_mutex	mtx_print;
	t_philo	*philos;
};

// MAIN
int		parse(t_data *data, char **argv);
int		init_forks(int total_forks, t_mutex **forks);
void	destroy_forks(int total_forks, t_mutex **forks);
int		init_philos(t_data *data);
void	free_philos(t_data *data);
void	start_simulation(t_data *data);
void	*routine(void *arg);

//  UTILS
t_mutex	*get_first_fork(t_philo *philo);
t_mutex	*get_second_fork(t_philo *philo);
int		exit_error(const char *error);
int		sleep_ml(long miliseconds);
long	gettmstmp(long start);
long	print_status(int status, t_philo *philo);
bool	check_status(t_philo *philo, int status);
bool	is_simulation_on(t_philo *philo);
void	stop_simulation(t_data *data, long philo_id);

#endif