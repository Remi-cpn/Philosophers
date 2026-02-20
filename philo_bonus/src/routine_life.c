/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_life.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 10:52:15 by rcompain          #+#    #+#             */
/*   Updated: 2026/02/20 16:56:48 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	sleeping(t_data *data, t_philo *philo)
{
	print(data, philo, "is sleeping", 0);
	waitting(data->sleep_time);
}

void	eating(t_philo *p, t_data *d)
{
	sem_wait(d->s_table);
	sem_wait(d->s_forks);
	print(d, p, "has taken a fork", 0);
	sem_wait(d->s_forks);
	print(d, p, "has taken a fork", 0);
	sem_wait(p->s_check_last_meal);
	p->last_meal = get_time_ms();
	p->nbr_meal++;
	if (d->count_meal == true && p->nbr_meal == d->nbr_meal)
		sem_post(d->s_meal_end);
	sem_post(p->s_check_last_meal);
	print(d, p, "is eating", 0);
	waitting(d->eat_time);
	sem_post(d->s_forks);
	print(d, p, "has drop a fork", 0);
	sem_post(d->s_forks);
	print(d, p, "has drop a fork", 0);
	sem_post(d->s_table);
}
