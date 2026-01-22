/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 14:40:21 by rcompain          #+#    #+#             */
/*   Updated: 2026/01/22 11:27:21 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include "stdlib.h"
# include "unistd.h"
# include "stdio.h"
# include <pthread.h>
# include <stdbool.h>

typedef enum e_error
{
	FAILURE = -1,
	SUCCES = 0,
	ERROR = 1,
}	t_error;

typedef struct s_data
{
	int				nbr_ph;
	int				death_time;
	int				eat_time;
	int				sleep_time;
	int				nbr_meal;
	pthread_mutex_t	*fork;
	bool			end;
	pthread_mutex_t	end_mutex;
}	t_data;

typedef struct s_philo
{
	char		id;
	bool		dead;
	pthread_t	thread;
	t_data		*data;
}	t_philo;

void	*routine(void *d);

/** Init */
void	init_data(t_data *data, char **av);
t_philo	*init_philos(t_data *data);

/** Utils */
int		ft_atoi_wich(char *s);
void	*ft_calloc(size_t nmemb, size_t size);

/** Exit */
void	exit_prog(t_data *data, t_philo *philos);

#endif