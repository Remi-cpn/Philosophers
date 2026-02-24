/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 11:43:12 by rcompain          #+#    #+#             */
/*   Updated: 2026/02/20 16:39:38 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static void	check_nbr_meal(t_data *data, t_monitor *m)
{
	int	i;

	if (data->count_meal == false)
		return ;
	i = 0;
	while (i < data->nbr_ph)
	{
		if (m->nbr_meal[i] == false)
			return ;
		i++;
	}
	pthread_mutex_lock(&m->data->end_mutex);
	m->data->end = true;
	pthread_mutex_unlock(&m->data->end_mutex);
}

static void	set_death(t_monitor *m, int i)
{
	pthread_mutex_lock(&m->data->end_mutex);
	m->data->end = true;
	pthread_mutex_unlock(&m->data->end_mutex);
	pthread_mutex_unlock(&m->philos[i].meal_mutex);
	print(m->data, &m->philos[i], "died", 1);
}

void	*monitoring(void *parms)
{
	t_monitor	*m;
	int			i;

	m = parms;
	i = 0;
	while (end(m->data) == false)
	{
		pthread_mutex_lock(&m->philos[i].meal_mutex);
		if (get_time_ms() - m->philos[i].last_meal
			> m->data->death_time)
		{
			set_death(m, i);
			return (NULL);
		}
		if (m->data->count_meal && m->philos[i].nbr_meal == m->data->nbr_meal)
			m->nbr_meal[i] = true;
		pthread_mutex_unlock(&m->philos[i].meal_mutex);
		i++;
		if (i == m->data->nbr_ph)
			i = 0;
		check_nbr_meal(m->data, m);
		usleep(500);
	}
	return (NULL);
}
