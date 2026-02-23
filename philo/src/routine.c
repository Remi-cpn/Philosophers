/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 11:40:53 by rcompain          #+#    #+#             */
/*   Updated: 2026/02/23 12:07:37 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	print(t_data *d, t_philo *philo, char *action, int flag_stop)
{
	long	current_time;

	pthread_mutex_lock(&d->print_mutex);
	if (!(end(d) == true && flag_stop == 0))
	{
		current_time = get_time_ms() - d->start_time;
		printf("[%ld] %d %s\n", current_time, philo->id + 1, action);
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
	print(data, philo, "is sleeping", 0);
	waitting(data->sleep_time);
}

static void	eating(t_philo *philo, t_data *data)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&data->fork[philo->id]);
		print(data, philo, "has taken a fork", 0);
		pthread_mutex_lock(&data->fork[(philo->id + 1) % data->nbr_ph]);
		print(data, philo, "has taken a fork", 0);
	}
	else
	{
		pthread_mutex_lock(&data->fork[(philo->id + 1) % data->nbr_ph]);
		print(data, philo, "has taken a fork", 0);
		pthread_mutex_lock(&data->fork[philo->id]);
		print(data, philo, "has taken a fork", 0);
	}
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = get_time_ms();
	philo->nbr_meal++;
	pthread_mutex_unlock(&philo->meal_mutex);
	print(data, philo, "is eating", 0);
	waitting(data->eat_time);
	pthread_mutex_unlock(&data->fork[philo->id]);
	print(data, philo, "has drop a fork", 0);
	pthread_mutex_unlock(&data->fork[(philo->id + 1) % data->nbr_ph]);
	print(data, philo, "has drop a fork", 0);
}

void	*routine(void *params)
{
	t_philo	*philo;

	philo = params;
	if (philo->id % 2 == 0)
		usleep(500);
	if (philo->data->nbr_ph < 2)
	{
		print(philo->data, philo, "has taken a fork", 0);
		waitting(philo->data->eat_time * 2);
	}
	while (end(philo->data) == false)
	{
		if (philo->data->nbr_ph > 1)
		{
			eating(philo, philo->data);
			sleeping(philo->data, philo);
			print(philo->data, philo, "is thinking", 0);
		}
		usleep(10);
	}
	return (NULL);
}
