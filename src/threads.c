/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 15:53:16 by sbalk             #+#    #+#             */
/*   Updated: 2024/01/09 15:58:41 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	start_threads(t_monitor *monitor, pthread_mutex_t *forks)
{
	pthread_t	monitor_thread;
	int			i;

	if (pthread_create(&monitor_thread, NULL, &monitor_threads,
			&monitor->philos) != 0)
		destroy_all(monitor, forks, "pthread_create() failed\n");
	i = 0;
	while (i < monitor->philos[0].num_of_philos)
	{
		if (pthread_create(&monitor->philos[i].thread, NULL, &philo_routine,
				&monitor->philos[i]) != 0)
			destroy_all(monitor, forks, "pthread_create() failed\n");
		i++;
	}
	i = 0;
	if (pthread_join(monitor_thread, NULL) != 0)
		destroy_all(monitor, forks, "pthread_join() failed\n");
	while (i < monitor->philos[0].num_of_philos)
	{
		if (pthread_join(monitor->philos[i].thread, NULL) != 0)
			destroy_all(monitor, forks, "pthread_join() failed\n");
		i++;
	}
	return (0);
}
