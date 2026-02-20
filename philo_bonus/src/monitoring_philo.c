/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring_philo.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 10:17:54 by rcompain          #+#    #+#             */
/*   Updated: 2026/02/20 09:24:01 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	*monitoring_check_end(void *params)
{
	t_philo	*p;

	p = params;
	sem_wait(p->data->s_end);
	sem_post(p->data->s_end);
	sem_wait(p->s_check_end);
	p->end = true;
	sem_post(p->s_check_end);
	return (NULL);
}

void	*monitoring_philo(void *params)
{
	t_philo	*p;

	p = params;
	while (end(p) == false)
	{
		sem_wait(p->s_check_last_meal);
		if (get_time_ms() - p->last_meal
			>= p->data->death_time)
		{
			print(p->data, p, "Died", 1);
			sem_wait(p->s_check_end);
			p->end = true;
			sem_post(p->s_check_end);
			sem_post(p->data->s_ph_dead);
			sem_post(p->s_check_last_meal);
			break ;
		}
		sem_post(p->s_check_last_meal);
		usleep(1000);
	}
	return (NULL);
}
