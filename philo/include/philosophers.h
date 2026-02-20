/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 14:40:21 by rcompain          #+#    #+#             */
/*   Updated: 2026/02/20 16:59:27 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <stdbool.h>
# include <limits.h>

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
	bool			count_meal;
	pthread_mutex_t	*fork;
	bool			end;
	pthread_mutex_t	end_mutex;
	long			start_time;
	pthread_mutex_t	print_mutex;
}	t_data;

typedef struct s_philo
{
	int				id;
	long			last_meal;
	int				nbr_meal;
	pthread_mutex_t	meal_mutex;
	pthread_t		thread;
	t_data			*data;
}	t_philo;

typedef struct s_monitor
{
	t_data		*data;
	t_philo		*philos;
	bool		*nbr_meal;
	pthread_t	thread;
}	t_monitor;

void	*routine(void *d);
void	*monitoring(void *parms);
bool	end(t_data *data);
void	print(t_data *data, t_philo *philo, char *action, int flag_death);

/** Init */
void	init_data(t_data *data, char **av, int *flag);
t_philo	*init_philos(t_data *data, int *flag);
void	init_monitor(t_data *data, t_philo *philos, t_monitor *m, int *flag);

/** Utils */
int		ft_atoi_wich(char *s);
void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_memset(void *s, int c, size_t n);
long	get_time_ms(void);
void	waitting(long time);

/** Exit */
void	exit_prog(t_data *data, t_philo *philos, t_monitor *monitor);

#endif
