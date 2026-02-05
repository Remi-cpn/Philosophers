/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 11:43:12 by rcompain          #+#    #+#             */
/*   Updated: 2026/01/23 14:52:53 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

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
			>= m->data->death_time)
		{
			pthread_mutex_lock(&m->data->end_mutex);
			m->data->end = true;
			pthread_mutex_unlock(&m->data->end_mutex);
			pthread_mutex_unlock(&m->philos[i].meal_mutex);
			print(m->data, &m->philos[i], "Dead", 1);
			return (NULL);
		}
		pthread_mutex_unlock(&m->philos[i].meal_mutex);
		i++;
		if (i == m->data->nbr_ph)
			i = 0;
		usleep(500);
	}
	return (NULL);
}
