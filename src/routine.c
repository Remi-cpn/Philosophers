/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 11:40:53 by rcompain          #+#    #+#             */
/*   Updated: 2026/01/22 11:48:43 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static void	take_fork()
{
	
}

static bool	end(t_data *data)
{
	bool	end;

	pthread_mutex_lock(&data->end_mutex);
	end = data->end;
	pthread_mutex_unlock(&data->end_mutex);
	if (end == true)
		return (true);
	return (false);
}

void	*routine(void *d)
{
	t_philo	*data;

	data = d;

	while (end(data) == false)
	{
		//prend fourchette
		//mange
		//poser fourchette
		//dormir
		//penser
	}
	return (NULL);
}
