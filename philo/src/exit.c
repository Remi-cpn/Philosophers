/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 10:36:47 by rcompain          #+#    #+#             */
/*   Updated: 2026/02/20 16:58:50 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static void	free_philos(t_philo *philos, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_ph)
	{
		pthread_mutex_destroy(&philos[i].meal_mutex);
		i++;
	}
	free(philos);
}

static void	free_data(t_data *data)
{
	pthread_mutex_destroy(&data->end_mutex);
	pthread_mutex_destroy(&data->print_mutex);
}

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

void	exit_prog(t_data *data, t_philo *philos, t_monitor *monitor)
{
	if (monitor && monitor->nbr_meal)
		free(monitor->nbr_meal);
	if (philos)
		free_philos(philos, data);
	if (data && data->fork)
		free_fork(data);
	free_data(data);
}
