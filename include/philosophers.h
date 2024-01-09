/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 12:12:54 by sbalk             #+#    #+#             */
/*   Updated: 2024/01/09 13:40:44 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>

# define MAX_PHILOSOPHERS 200




/********************************************************************/
/*                          UTILS                                   */
/********************************************************************/

// TIME
size_t	get_current_time(void);
int		ft_usleep(size_t milliseconds);

// STRING
int		ft_is_space(const char *ch);
size_t	ft_strlen(const char *str);
int		ft_atoi(const char *str);
void	ft_putstr_fd(char *s, int fd);
int		ft_is_str_num(char *str);

#endif