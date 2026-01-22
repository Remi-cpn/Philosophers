/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 10:22:45 by rcompain          #+#    #+#             */
/*   Updated: 2026/01/22 11:41:34 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

t_philo	*init_philos(t_data *data)
{
	t_philo		*philos;
	int			i;

	philos = ft_calloc(data->nbr_ph, sizeof(t_philo));
	i = 0;
	while (i < data->nbr_ph)
	{
		philos[i].id = '1' + i;
		philos[i].data = data;
		philos[i].dead = false;
		pthread_create(&philos[i].thread, NULL, routine, &philos[i]);
		i++;
	}
	i = 0;
	while (i < data->nbr_ph)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
	return (philos);
}

static void	init_fork(t_data *data)
{
	int	i;

	data->fork = malloc(sizeof(pthread_mutex_t) * data->nbr_ph);
	i = 0;
	while (i < data->nbr_ph)
	{
		pthread_mutex_init(&data->fork[i], NULL);
		i++;
	}
}

void	init_data(t_data *data, char **av)
{
	data->nbr_ph = ft_atoi_wich(av[1]);
	data->death_time = ft_atoi_wich(av[2]);
	data->eat_time = ft_atoi_wich(av[3]);
	data->sleep_time = ft_atoi_wich(av[4]);
	if (av[5])
		data->nbr_meal = ft_atoi_wich(av[5]);
	data->end = false;
	pthread_mutex_init(&data->end_mutex, NULL);
	init_fork(data);
}
