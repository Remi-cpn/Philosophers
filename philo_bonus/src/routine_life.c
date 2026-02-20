/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_life.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 10:52:15 by rcompain          #+#    #+#             */
/*   Updated: 2026/02/20 10:50:31 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	sleeping(t_data *data, t_philo *philo)
{
	print(data, philo, "Sleep", 0);
	waitting(data->sleep_time);
}

void	eating(t_philo *p, t_data *d)
{
	sem_wait(d->s_forks);
	sem_wait(d->s_forks);
	sem_wait(p->s_check_last_meal);
	p->last_meal = get_time_ms();
	p->nbr_meal++;
	if (d->count_meal == true && p->nbr_meal == d->nbr_meal)
		sem_post(d->s_meal_end);
	sem_post(p->s_check_last_meal);
	print(d, p, "Eat", 0);
	waitting(d->eat_time);
	sem_post(d->s_forks);
	sem_post(d->s_forks);
}
