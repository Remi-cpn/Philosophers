/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 14:39:49 by rcompain          #+#    #+#             */
/*   Updated: 2026/02/17 12:55:06 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"
#include <pthread.h>
#include <semaphore.h>

void	*monitoring(void *parms)
{

}

static void	build_philos(t_data *data)
{
	t_philo	philo;
	int		i;

	ft_memset(&philo, 0, sizeof(t_philo));
	data->pids = ft_calloc(data->nbr_ph, sizeof(pid_t));
	if (!data->pids)
		return ;
	while (i < data->nbr_ph)
	{
		philo.id = i;
		data->pids[i] = fork();
		if (data->pids[i] == 0)
			routine(data);
	}
	pthread_create(&data->monitoring_death, NULL, monitoring, data);
	while (1)
	{
		sem_wait(&data->death);
		if (data->end = true)

		sem_post(&data->death);
	}
}

int	main(int ac, char **av)
{
	t_data	data;
	int		flag;
	int		i;

	if (ac != 5 && ac != 6)
		return (ERROR);
	ft_memset(&data, 0, sizeof(t_data));
	flag = 0;
	init_data(&data, av, &flag);
	//init philo
	//fork enfant philos
	//boucle check semaphore mort
	//wait pid
	i = 0;
	while (i < data.nbr_ph)
	{
		waitpid(data.pids[i], 0, NULL);
		i++;
	}
}
