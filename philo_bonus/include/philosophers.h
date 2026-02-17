/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 14:40:21 by rcompain          #+#    #+#             */
/*   Updated: 2026/02/17 12:48:24 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include "stdlib.h"
# include "unistd.h"
# include "stdio.h"
# include <pthread.h>
# include <stdbool.h>

# include <semaphore.h>
# include <sys/wait.h>

typedef enum e_error
{
	FAILURE = -1,
	SUCCES = 0,
	ERROR = 1,
}	t_error;

typedef struct s_data
{
	pthread_t	monitoring_death;
	sem_t		forks;
	sem_t		death;
	pid_t		*pids;
	int			nbr_ph;
	int			death_time;
	int			eat_time;
	int			sleep_time;
	int			nbr_meal;
	bool		count_meal;
	bool		end;
	long		start_time;
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

void	routine(t_data *data);
void	*monitoring(void *parms);
bool	end(t_data *data);
void	print(t_data *data, t_philo *philo, char *action, int flag_death);

/** Init */
void	init_data(t_data *data, char **av, int *flag);
t_philo	init_philos(t_data *data);

/** Utils */
int		ft_atoi_wich(char *s);
void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_memset(void *s, int c, size_t n);
long	get_time_ms(void);
void	waitting(long time);

/** Exit */
void	exit_prog(t_data *data, t_philo *philos, t_monitor *monitor);

#endif
