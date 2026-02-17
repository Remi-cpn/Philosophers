/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 10:22:45 by rcompain          #+#    #+#             */
/*   Updated: 2026/02/17 12:42:54 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"
#include <pthread.h>
#include <limits.h>
#include <semaphore.h>

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

t_philo	init_philos(t_data *data)
{
	t_philo		philo;
	int			i;

	i = 0;
	while (i < data->nbr_ph)
	{
		philo.last_meal = get_time_ms();
		i++;
	}
	return (philo);
}

void	init_data(t_data *data, char **av, int *flag)
{
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
	*flag = sem_init(&data->forks, 0, data->nbr_ph);
	if (*flag == FAILURE)
		return ;
	sem_init(&data->death, 0, 1);
	if (*flag == FAILURE)
		return ;
}
