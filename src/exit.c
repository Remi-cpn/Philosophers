/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 10:36:47 by rcompain          #+#    #+#             */
/*   Updated: 2026/01/22 10:56:41 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static void	free_fork(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_ph)
	{
		pthread_mutex_destroy(&data->fork[i]);
		i++;
	}
	free(data->fork);
}

void	exit_prog(t_data *data, t_philo *philos)
{
	if (data->fork)
		free_fork(data);
	free(philos);
}
