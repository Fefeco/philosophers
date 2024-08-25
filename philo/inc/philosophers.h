/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcarranz <fcarranz@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 09:02:08 by fcarranz          #+#    #+#             */
/*   Updated: 2024/08/25 12:20:58 by fcarranz         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef PHILISOPHERS_H
# define PHILOSOPHERS_H
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <stdbool.h>

typedef struct s_philo
{
	int				id;
	bool			alive;
	struct s_philo	*prev;
	struct s_philo	*next;
	
}	t_philo;

#endif