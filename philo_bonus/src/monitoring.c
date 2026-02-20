/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 11:43:12 by rcompain          #+#    #+#             */
/*   Updated: 2026/02/20 13:54:03 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"
#include <signal.h>

void	*monitoring_meal(void *params)
{
	int		i;
	t_data	*d;

	d = params;
	i = 0;
	while (i < d->nbr_ph)
	{
		sem_wait(d->s_meal_end);
		i++;
	}
	sem_post(d->s_end);
	if (d->ph_dead == false)
		print(d, NULL, "all the philosophers ate", 2);
	sem_post(d->s_ph_dead);
	return (NULL);
}

void	*monitoring_ph_dead(void *params)
{
	t_data	*d;
	int		i;

	d = params;
	sem_wait(d->s_ph_dead);
	sem_post(d->s_end);
	d->ph_dead = true;
	i = 0;
	while (d->count_meal == true && i < d->nbr_ph)
	{
		sem_post(d->s_meal_end);
		i++;
	}
	return (NULL);
}
