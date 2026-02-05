/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 11:40:53 by rcompain          #+#    #+#             */
/*   Updated: 2026/02/05 14:48:27 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"
#include <pthread.h>
#include <string.h>
#include <unistd.h>

void	print(t_data *d, t_philo *philo, char *action, int flag_stop)
{
	long	current_time;

	pthread_mutex_lock(&d->print_mutex);
	if (!(end(d) == true && flag_stop == 0))
	{
		current_time = get_time_ms() - d->start_time;
		if (flag_stop == 2)
			printf("[%ld] => %s %d times\n", current_time, action, d->nbr_meal);
		else
			printf("[%ld] %d => %s\n", current_time, philo->id + 1, action);
	}
	pthread_mutex_unlock(&d->print_mutex);
}

bool	end(t_data *data)
{
	bool	end;

	pthread_mutex_lock(&data->end_mutex);
	end = data->end;
	pthread_mutex_unlock(&data->end_mutex);
	if (end == true)
		return (true);
	return (false);
}

static void	sleeping(t_data *data, t_philo *philo)
{
	int	time;

	time = 0;
	print(data, philo, "Sleep", 0);
	waitting(data->sleep_time);
}

static void	eating(t_philo *philo, t_data *data)
{
	int	time;

	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&data->fork[philo->id]);
		pthread_mutex_lock(&data->fork[(philo->id + 1) % data->nbr_ph]);
	}
	else
	{
		pthread_mutex_lock(&data->fork[(philo->id + 1) % data->nbr_ph]);
		pthread_mutex_lock(&data->fork[philo->id]);
	}
	time = 0;
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = get_time_ms();
	philo->nbr_meal++;
	pthread_mutex_unlock(&philo->meal_mutex);
	print(data, philo, "Eat", 0);
	waitting(data->eat_time);
	pthread_mutex_unlock(&data->fork[philo->id]);
	pthread_mutex_unlock(&data->fork[(philo->id + 1) % data->nbr_ph]);
}

void	*routine(void *params)
{
	t_philo	*philo;

	philo = params;
	if (philo->id % 2 == 0)
		usleep(500);
	while (end(philo->data) == false)
	{
		if (philo->data->nbr_ph > 1)
		{
			eating(philo, philo->data);
			sleeping(philo->data, philo);
			print(philo->data, philo, "Think", 0);
		}
		usleep(10);
	}
	return (NULL);
}
