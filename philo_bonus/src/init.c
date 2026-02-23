/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 10:22:45 by rcompain          #+#    #+#             */
/*   Updated: 2026/02/23 12:02:35 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	init_semaphores(t_data *d)
{
	d->s_end = sem_open("/end", O_CREAT, 0644, 0);
	if (d->s_end == SEM_FAILED)
		return (ERROR);
	sem_unlink("/end");
	d->s_meal_end = sem_open("/meal_end", O_CREAT, 0644, 0);
	if (d->s_meal_end == SEM_FAILED)
		return (ERROR);
	sem_unlink("/meal_end");
	d->s_print = sem_open("/print", O_CREAT, 0644, 1);
	if (d->s_print == SEM_FAILED)
		return (ERROR);
	sem_unlink("/print");
	d->s_forks = sem_open("/forks", O_CREAT, 0644, d->nbr_ph);
	if (d->s_forks == SEM_FAILED)
		return (ERROR);
	sem_unlink("/forks");
	d->s_ph_dead = sem_open("/ph_dead", O_CREAT, 0644, 0);
	if (d->s_ph_dead == SEM_FAILED)
		return (ERROR);
	sem_unlink("/ph_dead");
	d->s_table = sem_open("/table", O_CREAT, 0644, 1);
	if (d->s_table == SEM_FAILED)
		return (ERROR);
	sem_unlink("/table");
	return (SUCCES);
}

t_philo	init_philos(t_data *data)
{
	t_philo		philo;

	ft_memset(&philo, 0, sizeof(t_philo));
	philo.last_meal = get_time_ms();
	philo.data = data;
	return (philo);
}

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
	data->pids = ft_calloc(data->nbr_ph, sizeof(pid_t));
	if (!data->pids)
		*flag = ERROR;
}
