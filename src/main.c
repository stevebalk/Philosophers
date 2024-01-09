/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 12:11:00 by sbalk             #+#    #+#             */
/*   Updated: 2024/01/09 16:43:33 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Check if argment count and arguments are valid
// returns 1 if invalid, 0 if valid
int	input_check(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (ft_putstr_fd("Error: wrong number of arguments\n", 2), 1);
	if (ft_atoi(argv[1]) > MAX_PHILOSOPHERS || ft_atoi(argv[1]) <= 0 ||
		ft_is_str_num(argv[1]) == 0)
		return (ft_putstr_fd("Error: Philosophers: Invalid number\n", 2), 1);
	if (ft_atoi(argv[2]) <= 0 || ft_is_str_num(argv[2]) == 0)
		return (ft_putstr_fd("Error: Time to die: Invalid number\n", 2), 1);
	if (ft_atoi(argv[3]) <= 0 || ft_is_str_num(argv[3]) == 0)
		return (ft_putstr_fd("Error: Time to eat: Invalid number\n", 2), 1);
	if (ft_atoi(argv[4]) <= 0 || ft_is_str_num(argv[4]) == 0)
		return (ft_putstr_fd("Error: Time to sleep: Invalid number\n", 2), 1);
	if (argv[5] && (ft_atoi(argv[5]) < 0 || ft_is_str_num(argv[5]) == 0))
		return (ft_putstr_fd("Error: Meals must eat: Invalid number\n", 2), 1);
	return (0);
}

// void	*observe_thread(void *arg)
// {
// 	t_philo	*philo;

// 	philo = (t_philo *)arg;
// 	while (1)
// 	{
// 		pthread_mutex_lock(philo->dead_lock);
// 		if (philo->dead == 1)
// 		{
// 			pthread_mutex_unlock(philo->dead_lock);
// 			return (NULL);
// 		}
// 		pthread_mutex_unlock(philo->dead_lock);
// 		pthread_mutex_lock(philo->meal_lock);
// 		if (philo->meals_eaten == philo->meals_to_eat)
// 		{
// 			pthread_mutex_unlock(philo->meal_lock);
// 			return (NULL);
// 		}
// 		pthread_mutex_unlock(philo->meal_lock);
// 	}
// }


int	main(int argc, char **argv)
{
	t_monitor		monitor;
	t_philo			philos[MAX_PHILOSOPHERS];
	pthread_mutex_t	forks[MAX_PHILOSOPHERS];

	if (input_check(argc, argv))
		return (1);
	init(argv, philos, &monitor, forks);
	start_threads(&monitor, forks);
	destroy_all(&monitor, forks, NULL);
	return (EXIT_SUCCESS);
}
