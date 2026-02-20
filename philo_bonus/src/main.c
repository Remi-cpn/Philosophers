/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 14:39:49 by rcompain          #+#    #+#             */
/*   Updated: 2026/02/20 16:57:01 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static void	close_sem(t_data *d)
{
	sem_close(d->s_end);
	sem_close(d->s_forks);
	sem_close(d->s_print);
	sem_close(d->s_ph_dead);
	sem_close(d->s_meal_end);
	sem_close(d->s_table);
}

static void	wait_philo(t_data *d)
{
	int	i;

	i = 0;
	while (i < d->nbr_ph)
	{
		waitpid(d->pids[i], NULL, 0);
		i++;
	}
}

static int	fork_philo(t_data *d)
{
	t_philo	philo;
	int		i;

	i = 0;
	while (i < d->nbr_ph)
	{
		d->pids[i] = fork ();
		if (d->pids[i] == CHILD)
		{
			philo = init_philos(d);
			philo.id = i;
			routine(d, &philo);
			exit(0);
		}
		if (d->pids[i] == FAILURE)
		{
			sem_post(d->s_end);
			return (ERROR);
		}
		i++;
	}
	return (SUCCES);
}

int	main(int ac, char **av)
{
	t_data	data;
	int		flag;

	if (ac != 5 && ac != 6)
		return (ERROR);
	ft_memset(&data, 0, sizeof(t_data));
	flag = 0;
	init_data(&data, av, &flag);
	if (flag == FAILURE)
		return (ERROR);
	init_semaphores(&data);
	flag = fork_philo(&data);
	if (flag == SUCCES)
	{
		pthread_create(&(data.m_parent), NULL, monitoring_ph_dead, &data);
		if (data.count_meal == true)
			pthread_create(&(data.m_meal_end), NULL, monitoring_meal, &data);
		wait_philo(&data);
		pthread_join(data.m_parent, NULL);
		if (data.count_meal == true)
			pthread_join(data.m_meal_end, NULL);
	}
	close_sem(&data);
	free(data.pids);
	return (0);
}
