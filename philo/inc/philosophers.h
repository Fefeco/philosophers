/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcarranz <fcarranz@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 09:02:08 by fcarranz          #+#    #+#             */
/*   Updated: 2024/09/10 10:48:24 by fcarranz         ###   ########.fr       */
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
// # GRN	Green text
// # GRY	Gray text
// # YLW	Yellow text
// # BLU	Blue text
// # MGN	Magenta text
// # CYN	Cyan text
// # WHT	White text
// # RST 	Reset to default
// # CLS	Clear screen
# define RED "\033[1;31m"
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

typedef pthread_mutex_t	t_mutex;
typedef pthread_t		t_thd;
typedef struct s_data	t_data;
typedef struct s_philo	t_philo;
typedef enum e_status	t_status;

enum e_status
{
	SLEPING,
	EATING,
	THINKING,
	FULL,
	DEAD,
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
	t_philo	*philos;
};

// MAIN
int		parse(t_data *data, char **argv);
int		init_structs(t_data *data);
int		init_forks(int total_forks, t_mutex **forks);
void	destroy_forks(int total_forks, t_mutex **forks);
int		init_philos(t_data *data);
void	free_philos(t_data *data);
void	start_simulation(t_data *data);
void	*routine(void *arg);
int		change_status(t_philo *philo, int new_status);

//  UTILS
t_mutex	*get_first_fork(t_philo *philo);
t_mutex	*get_second_fork(t_philo *philo);
int		ft_strlen(char *str);
int		exit_error(const char *error);
int		sleep_ml(long miliseconds);
int		init_forks(int total_forks, t_mutex **forks);
long	gettmstmp(long start);
void	print_status(int status, long id, long timestamp);
bool	is_simulation_on(t_philo *philo);

#endif