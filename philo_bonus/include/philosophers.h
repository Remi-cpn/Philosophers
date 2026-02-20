/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 14:40:21 by rcompain          #+#    #+#             */
/*   Updated: 2026/02/20 16:55:34 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <stdio.h>
# include <pthread.h>
# include <stdbool.h>
# include <fcntl.h>
# include <semaphore.h>
# include <sys/wait.h>

# define CHILD 0

typedef enum e_error
{
	FAILURE = -1,
	SUCCES = 0,
	ERROR = 1,
}	t_error;

typedef struct s_data
{
	pthread_t	m_parent;
	pthread_t	m_meal_end;
	sem_t		*s_meal_end;
	bool		count_meal;
	int			nbr_meal;
	sem_t		*s_forks;
	sem_t		*s_end;
	sem_t		*s_table;
	sem_t		*s_print;
	sem_t		*s_ph_dead;
	pid_t		*pids;
	bool		end;
	int			nbr_ph;
	int			death_time;
	int			eat_time;
	int			sleep_time;
	long		start_time;
}	t_data;

typedef struct s_philo
{
	int			id;
	long		last_meal;
	sem_t		*s_check_last_meal;
	bool		end;
	sem_t		*s_check_end;
	int			nbr_meal;
	pthread_t	m_philo;
	pthread_t	m_check_end;
	t_data		*data;
}	t_philo;

/* routine.c */
void	routine(t_data *data, t_philo *philo);

/* routine_life.c */
void	eating(t_philo *p, t_data *d);
void	sleeping(t_data *data, t_philo *philo);

/* routine_utils.c */
bool	end(t_philo *p);
void	waitting(long time);
void	print(t_data *data, t_philo *philo, char *action, int flag_death);

/* monitoring.c */
void	*monitoring_ph_dead(void *parms);
void	*monitoring_meal(void *params);

/* monitoring_philo.c */
void	*monitoring_philo(void *params);
void	*monitoring_check_end(void *params);

/* init.c */
void	init_data(t_data *data, char **av, int *flag);
t_philo	init_philos(t_data *data);
int		init_semaphores(t_data *d);

/* utils.c */
int		ft_atoi_wich(char *s);
char	*ft_itoa_wich(int n);
char	*ft_strjoin_wich(char *s1, char *s2, size_t size_s1);
void	*ft_memset(void *s, int c, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
long	get_time_ms(void);

#endif
