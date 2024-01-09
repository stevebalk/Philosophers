/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 15:51:12 by sbalk             #+#    #+#             */
/*   Updated: 2024/01/09 16:05:15 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Check if a philosopher is dead/dead flag set
int	philo_is_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (philo[0].dead == 1)
	{
		pthread_mutex_unlock(philo->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

void	*philo_routine(void *pointer)
{
	t_philo	*philo;

	philo = (t_philo *)pointer;
	while (!philo_is_dead(philo))
	{
			philo_eat(philo);
			philo_sleep(philo);
			philo_think(philo);
	}
	return (pointer);
}