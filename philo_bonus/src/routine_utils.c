/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 10:59:56 by rcompain          #+#    #+#             */
/*   Updated: 2026/02/20 10:57:43 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	print(t_data *d, t_philo *p, char *action, int flag_stop)
{
	long	current_time;

	sem_wait(d->s_print);
	if (!(end(p) == true && flag_stop == 0))
	{
		current_time = get_time_ms() - d->start_time;
		if (flag_stop == 2)
			printf("[%ld] => %s %d times\n", current_time, action, d->nbr_meal);
		else
			printf("[%ld] %d => %s\n", current_time, p->id + 1, action);
	}
	sem_post(d->s_print);
}

bool	end(t_philo *p)
{
	bool	end;

	if (!p)
		return (true);
	sem_wait(p->s_check_end);
	end = p->end;
	sem_post(p->s_check_end);
	if (end == true)
		return (true);
	return (false);
}

void	waitting(long time)
{
	long	current;

	current = get_time_ms();
	while ((get_time_ms() - current) < time)
		usleep(500);
}
