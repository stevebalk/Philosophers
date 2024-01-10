/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 12:11:00 by sbalk             #+#    #+#             */
/*   Updated: 2024/01/10 15:27:30 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Checks if wrong user input
// Between 4 and 5 arguments
// Arguments are numbers
// Arguments are positive
// Number of philosophers is not greater than MAX_PHILOSOPHERS
int	is_wrong_input(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (ft_putstr_fd("Error: wrong number of arguments\n", 2), 1);
	if (ft_atoi(argv[1]) > MAX_PHILOSOPHERS || ft_atoi(argv[1]) <= 0
		|| ft_is_str_num(argv[1]) == 0)
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

int	main(int argc, char **argv)
{
	t_monitor		monitor;
	t_philo			philos[MAX_PHILOSOPHERS];
	pthread_mutex_t	forks[MAX_PHILOSOPHERS];

	if (is_wrong_input(argc, argv))
		return (1);
	init(argv, philos, &monitor, forks);
	start_threads(&monitor, forks);
	destroy_all(&monitor, forks, NULL);
	return (EXIT_SUCCESS);
}
