/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:21:41 by sbalk             #+#    #+#             */
/*   Updated: 2024/01/09 16:42:50 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	destroy_all(t_monitor *monitor, pthread_mutex_t *forks, char *str)
{
	int	i;

	i = 0;
	if (str != NULL)
		ft_putstr_fd(str, 2);
	pthread_mutex_destroy(&monitor->dead_lock);
	pthread_mutex_destroy(&monitor->meal_lock);
	pthread_mutex_destroy(&monitor->write_lock);
	while (i < monitor->philos[0].num_of_philos)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
}
