/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 14:39:49 by rcompain          #+#    #+#             */
/*   Updated: 2026/02/24 15:02:25 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static void	join(t_data *data, t_philo *philos, int i)
{
	int	j;

	if (i != data->nbr_ph)
	{
		pthread_mutex_lock(&(data->end_mutex));
		data->end = true;
		pthread_mutex_unlock(&(data->end_mutex));
	}
	j = 0;
	while (j < i)
	{
		pthread_join(philos[j].thread, NULL);
		j++;
	}
}

static void	exec(t_data *data, t_philo *philos, t_monitor *monitor)
{
	int		i;
	int		flag;

	i = 0;
	flag = 0;
	while (flag == 0 && i < data->nbr_ph)
	{
		if (pthread_create(&philos[i].thread, NULL, routine, &philos[i]) != 0)
			flag = 1;
		else
			i++;
	}
	if (flag == 0)
	{
		if (pthread_create(&monitor->thread, NULL, monitoring, monitor) != 0)
		{
			pthread_mutex_lock(&(data->end_mutex));
			data->end = true;
			pthread_mutex_unlock(&(data->end_mutex));
		}
		else
			pthread_join(monitor->thread, NULL);
	}
	join(data, philos, i);
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
