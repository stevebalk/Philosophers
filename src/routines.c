/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 15:51:12 by sbalk             #+#    #+#             */
/*   Updated: 2024/01/09 16:41:50 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Check if a philosopher is dead/dead flag set
static int	is_dead_flag_set(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead == 1)
	{
		pthread_mutex_unlock(philo->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

static void	thinking(t_philo *philo)
{
	print_philo_status(philo, philo->id, "is thinking");
}

static void	sleeping(t_philo *philo)
{
	print_philo_status(philo, philo->id, "is sleeping");
	ft_usleep(philo->time_to_sleep);
}

static void	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	print_philo_status(philo, philo->id, "has taken a fork");
	if (philo->num_of_philos == 1)
	{
		ft_usleep(philo->time_to_die);
		pthread_mutex_unlock(philo->r_fork);
		return ;
	}
	pthread_mutex_lock(philo->l_fork);
	print_philo_status(philo, philo->id, "has taken a fork");
	philo->eating = 1;
	print_philo_status(philo, philo->id, "is eating");
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = get_current_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
	ft_usleep(philo->time_to_eat);
	philo->eating = 0;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	*philo_routine(void *pointer)
{
	t_philo	*philo;

	philo = (t_philo *)pointer;
	while (!is_dead_flag_set(philo))
	{
			eating(philo);
			sleeping(philo);
			thinking(philo);
	}
	return (pointer);
}
