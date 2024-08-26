/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcarranz <fcarranz@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 12:08:12 by fcarranz          #+#    #+#             */
/*   Updated: 2024/08/26 12:53:20 by fcarranz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (*str++)
		++len;
	return (len);
}

void	exit_error(const char *error)
{
	write (2, "\v\v\v", 3);
	write (2, error, ft_strlen((char *)error));
	write (2, "\v\v\v", 3);
	exit(EXIT_FAILURE);
}
