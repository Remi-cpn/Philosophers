/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 11:43:12 by rcompain          #+#    #+#             */
/*   Updated: 2026/02/20 16:28:15 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

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
	i = 0;
	while (d->count_meal == true && i < d->nbr_ph)
	{
		sem_post(d->s_meal_end);
		i++;
	}
	return (NULL);
}
