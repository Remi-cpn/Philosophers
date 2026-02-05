/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 14:39:49 by rcompain          #+#    #+#             */
/*   Updated: 2026/02/05 14:38:10 by rcompain         ###   ########.fr       */
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
	int			flag;

	if (ac != 5 && ac != 6)
		return (ERROR);
	ft_memset(&data, 0, sizeof(t_data));
	ft_memset(&monitor, 0, sizeof(t_monitor));
	philos = NULL;
	flag = SUCCES;
	init_data(&data, av, &flag);
	philos = NULL;
	philos = init_philos(&data, &flag);
	init_monitor(&data, philos, &monitor, &flag);
	if (flag == SUCCES)
		exec(&data, philos, &monitor);
	exit_prog(&data, philos, &monitor);
	return (SUCCES);
}
