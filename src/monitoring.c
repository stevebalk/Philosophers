/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 15:50:33 by sbalk             #+#    #+#             */
/*   Updated: 2024/01/09 15:56:23 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_philo_status(t_philo *philo, int id, char *msg)
{
	pthread_mutex_lock(philo->write_lock);
	printf("%zu %d %s\n", get_current_time() - philo->start_time
		, philo->id, msg);
	pthread_mutex_unlock(philo->write_lock);
}

// Check if a philo has died
int	is_philo_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->meal_lock);
	if (get_current_time() - philo->last_meal >= philo->time_to_die
		&& philo->eating == 0)
		return (pthread_mutex_unlock(philo->meal_lock), 1);
	return (pthread_mutex_unlock(philo->meal_lock), 0);
}


// Checks every philo to see if one has died
int	has_a_philo_died(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->num_of_philos)
	{
		if (is_philo_dead(&philo[i]))
		{
			print_philo_status(&philo[i], philo[i].id, "died");
			pthread_mutex_lock(philo[0].dead_lock);
			philo[0].dead = 1;
			pthread_mutex_unlock(philo[0].dead_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

// Checks if all philos have eaten
int	did_all_ate(t_philo *philos)
{
	int	i;

	i = 0;
	if (philos[0].meals_to_eat == -1)
		return (0);
	while (i < philos->num_of_philos)
	{
		pthread_mutex_lock(philos[i].meal_lock);
		if (philos[i].meals_eaten != philos[i].meals_to_eat)
		{
			pthread_mutex_unlock(philos[i].meal_lock);
			return (0);
		}
		pthread_mutex_unlock(philos[i].meal_lock);
		i++;
	}
	philos[0].dead = 1;
	return (1);
}

void	*monitor_threads(void *pointer)
{
	t_philo	*philos;
	int		i;

	philos = (t_philo *)pointer;
	while (1)
	{
		if (has_a_philo_died(philos) || did_all_ate(philos))
			break ;
	}
	return (pointer);
}
