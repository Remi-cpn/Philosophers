/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 10:22:45 by rcompain          #+#    #+#             */
/*   Updated: 2026/02/05 15:03:50 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"
#include <pthread.h>
#include <limits.h>

static void	data_control_value(t_data *data, int *flag)
{
	if (data->nbr_ph < 1 || data->death_time < 0 || data->sleep_time < 0
		|| data->eat_time < 0)
		*flag = ERROR;
	if (data->nbr_ph > INT_MAX || data->death_time > INT_MAX
		|| data->sleep_time > INT_MAX || data->eat_time > INT_MAX)
		*flag = ERROR;
	if (data->count_meal == true && data->nbr_meal < 0)
		*flag = ERROR;
	if (data->count_meal == true && data->nbr_meal == 0)
	{
		*flag = ERROR;
		printf("No philosopher should eat.\n");
	}
}

void	init_monitor(t_data *data, t_philo *philos, t_monitor *m, int *flag)
{
	if (*flag == ERROR)
		return ;
	m->data = data;
	m->philos = philos;
	m->nbr_meal = NULL;
	if (data->count_meal == true)
	{
		m->nbr_meal = ft_calloc(data->nbr_ph, sizeof(bool));
		if (!m->nbr_meal)
			*flag = ERROR;
	}
}

t_philo	*init_philos(t_data *data, int *flag)
{
	t_philo		*philos;
	int			i;

	if (*flag == ERROR)
		return (NULL);
	philos = ft_calloc(data->nbr_ph, sizeof(t_philo));
	if (!philos)
		*flag = ERROR;
	i = 0;
	while (*flag == SUCCES && i < data->nbr_ph)
	{
		philos[i].id = i;
		philos[i].data = data;
		philos[i].last_meal = get_time_ms();
		pthread_mutex_init(&philos[i].meal_mutex, NULL);
		i++;
	}
	return (philos);
}

static void	init_fork(t_data *data, int *flag)
{
	int	i;

	data->fork = ft_calloc(data->nbr_ph, sizeof(pthread_mutex_t));
	if (!data->fork)
		*flag = ERROR;
	i = 0;
	while (*flag == SUCCES && i < data->nbr_ph)
	{
		pthread_mutex_init(&data->fork[i], NULL);
		i++;
	}
}

void	init_data(t_data *data, char **av, int *flag)
{
	pthread_mutex_init(&data->end_mutex, NULL);
	pthread_mutex_init(&data->print_mutex, NULL);
	data->nbr_ph = ft_atoi_wich(av[1]);
	data->death_time = ft_atoi_wich(av[2]);
	data->eat_time = ft_atoi_wich(av[3]);
	data->sleep_time = ft_atoi_wich(av[4]);
	data->count_meal = false;
	if (av[5])
	{
		data->count_meal = true;
		data->nbr_meal = ft_atoi_wich(av[5]);
	}
	data->end = false;
	data->start_time = get_time_ms();
	data_control_value(data, flag);
	init_fork(data, flag);
}
