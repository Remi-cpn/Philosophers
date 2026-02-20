/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 11:40:53 by rcompain          #+#    #+#             */
/*   Updated: 2026/02/20 16:55:46 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static void	end_routine(t_philo *p)
{
	if (p->m_check_end)
		pthread_join(p->m_check_end, NULL);
	if (p->m_philo)
		pthread_join(p->m_philo, NULL);
	if (p->s_check_last_meal)
		sem_close(p->s_check_last_meal);
	if (p->s_check_end)
		sem_close(p->s_check_end);
}

static sem_t	*init_sem(t_philo *p, char *name, size_t size_name)
{
	char	*id;
	char	*s;
	sem_t	*sem;

	id = ft_itoa_wich(p->id);
	if (!id)
		return (NULL);
	s = ft_strjoin_wich(name, id, size_name);
	if (!s)
		return (NULL);
	sem = sem_open(s, O_CREAT, 0644, 1);
	if (sem == SEM_FAILED)
		sem = NULL;
	sem_unlink(s);
	free(s);
	return (sem);
}

static int	init_routine(t_philo *p)
{
	p->s_check_last_meal = init_sem(p, "/last_meal_", 11);
	if (!p->s_check_last_meal)
		return (ERROR);
	p->s_check_end = init_sem(p, "/end_", 5);
	if (!p->s_check_end)
		return (ERROR);
	pthread_create(&(p->m_philo), NULL, monitoring_philo, p);
	pthread_create(&(p->m_check_end), NULL, monitoring_check_end, p);
	return (SUCCES);
}

void	routine(t_data *d, t_philo *p)
{
	int	flag;

	flag = init_routine(p);
	if (flag != ERROR && p->id % 2 == 0)
		usleep(50);
	if (d->nbr_ph < 2)
		print(d, p, "has taken a fork", 0);
	while (flag != ERROR && end(p) == false)
	{
		if (d->nbr_ph > 1)
		{
			eating(p, d);
			sleeping(d, p);
			print(d, p, "is thinking", 0);
		}
		usleep(10);
	}
	sem_post(d->s_end);
	end_routine(p);
	free(d->pids);
	exit(flag);
}
