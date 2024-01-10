/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 15:53:16 by sbalk             #+#    #+#             */
/*   Updated: 2024/01/10 13:00:48 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Starts the threads
// Monitor thread is created first, then the philo threads
// The philo threads are joined first, then the monitor thread

int	start_threads(t_monitor *monitor, pthread_mutex_t *forks)
{
	pthread_t	monitor_thread;
	int			i;

	if (pthread_create(&monitor_thread, NULL, &monitor_threads,
			monitor->philos) != 0)
		destroy_all(monitor, forks, "pthread_create() failed\n");
	i = 0;
	while (i < monitor->philos[0].num_of_philos)
	{
		if (pthread_create(&monitor->philos[i].thread, NULL, &philo_routine,
				&monitor->philos[i]) != 0)
			destroy_all(monitor, forks, "pthread_create() failed\n");
		i++;
	}
	if (pthread_join(monitor_thread, NULL) != 0)
		destroy_all(monitor, forks, "pthread_join() failed\n");
	i = 0;
	while (i < monitor->philos[0].num_of_philos)
	{
		if (pthread_join(monitor->philos[i].thread, NULL) != 0)
			destroy_all(monitor, forks, "pthread_join() failed\n");
		i++;
	}
	return (0);
}
