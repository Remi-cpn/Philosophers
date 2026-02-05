/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 14:39:49 by rcompain          #+#    #+#             */
/*   Updated: 2026/01/23 14:28:21 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static void	exec(t_data *data, t_philo *philos, t_monitor *monitor)
{
	int			i;

	i = 0;
	while (i < data->nbr_ph)
	{
		pthread_create(&philos[i].thread, NULL, routine, &philos[i]);
		i++;
	}
	pthread_create(&monitor->thread, NULL, monitoring, monitor);
	pthread_join(monitor->thread, NULL);
	i = 0;
	while (i < data->nbr_ph)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_data		data;
	t_philo		*philos;
	t_monitor	monitor;

	if (ac != 5 && ac != 6)
		return (ERROR);
	init_data(&data, av);
	philos = init_philos(&data);
	init_monitor(&data, philos, &monitor);
	exec(&data, philos, &monitor);
	exit_prog(&data, philos);
	return (SUCCES);
}
