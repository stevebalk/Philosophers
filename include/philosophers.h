/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 12:12:54 by sbalk             #+#    #+#             */
/*   Updated: 2024/01/10 14:11:04 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>

# define MAX_PHILOSOPHERS	200
# define START_DELAY		1

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
	int				num_of_philos;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				meals_to_eat;
	int				eating;
	int				meals_eaten;
	size_t			last_meal;
	size_t			start_time;
	int				*dead;
}					t_philo;

typedef struct s_monitor
{
	int				dead_flag;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	t_philo			*philos;
}					t_monitor;


/********************************************************************/
/*                          INIT                                    */
/********************************************************************/

void	init(char **argv, t_philo *philos, t_monitor *monitor
		, pthread_mutex_t *forks);

/********************************************************************/
/*                          THREADS                                 */
/********************************************************************/

int		start_threads(t_monitor *monitor, pthread_mutex_t *forks);

/********************************************************************/
/*                          PHILO_ROUTINE                           */
/********************************************************************/

void	*philo_routine(void *pointer);
int		is_dead_flag_set(t_philo *philo);

/********************************************************************/
/*                          Monitoring                              */
/********************************************************************/

void	*monitor_threads(void *pointer);

/********************************************************************/
/*                          UTILS                                   */
/********************************************************************/

// Philo
void	print_philo_status(t_philo *philo, int id, char *msg);
int		is_philo_dead(t_philo *philo, size_t time_to_die);
int		has_a_philo_died(t_philo *philo);
int		did_all_ate(t_philo *philos);

// TIME
size_t	get_current_time(void);
int		ft_usleep(size_t milliseconds);

// STRING
int		ft_is_space(const char *ch);
size_t	ft_strlen(const char *str);
int		ft_atoi(const char *str);
void	ft_putstr_fd(char *s, int fd);
int		ft_is_str_num(char *str);

// Free
void	destroy_all(t_monitor *monitor, pthread_mutex_t *forks, char *str);
#endif