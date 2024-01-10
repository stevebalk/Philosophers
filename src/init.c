/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 15:54:17 by sbalk             #+#    #+#             */
/*   Updated: 2024/01/10 14:13:09 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	init_input(char **argv, t_philo *philos)
{
	int	i;
	int	num_of_philos;

	i = 0;
	num_of_philos = ft_atoi(argv[1]);
	while (i < num_of_philos)
	{
		philos[i].num_of_philos = ft_atoi(argv[1]);
		philos[i].time_to_die = ft_atoi(argv[2]);
		philos[i].time_to_eat = ft_atoi(argv[3]);
		philos[i].time_to_sleep = ft_atoi(argv[4]);
		if (argv[5])
			philos[i].meals_to_eat = ft_atoi(argv[5]);
		else
			philos[i].meals_to_eat = -1;
		i++;
	}
}

static void	init_monitoring(t_monitor *monitor, t_philo *philos)
{
	monitor->dead_flag = 0;
	monitor->philos = philos;
	pthread_mutex_init(&monitor->dead_lock, NULL);
	pthread_mutex_init(&monitor->meal_lock, NULL);
	pthread_mutex_init(&monitor->write_lock, NULL);
}

static void	init_forks(pthread_mutex_t *forks, int num_of_philos)
{
	int	i;

	i = 0;
	while (i < num_of_philos)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

static void	init_philos(t_philo *philos, t_monitor *monitor ,pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < philos->num_of_philos)
	{
		philos[i].id = i + 1;
		philos[i].write_lock = &monitor->write_lock;
		philos[i].dead_lock = &monitor->dead_lock;
		philos[i].meal_lock = &monitor->meal_lock;
		philos[i].eating = 0;
		philos[i].meals_eaten = 0;
		philos[i].last_meal = get_current_time();
		philos[i].start_time = get_current_time();
		philos[i].dead = &monitor->dead_flag;
		philos[i].l_fork = &forks[i];
		philos[i].r_fork = &forks[(i + 1) % philos->num_of_philos];
		// printf("time to sleep: %zu\n", philos[i].time_to_sleep);
		i++;
	}
}

void	init(char **argv, t_philo *philos, t_monitor *monitor
		, pthread_mutex_t *forks)
{
	init_monitoring(monitor, philos);
	init_forks(forks, ft_atoi(argv[1]));
	init_input(argv, philos);
	init_philos(philos, monitor, forks);
}
