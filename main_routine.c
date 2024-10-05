/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_routine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drabarza <drabarza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 13:56:59 by drabarza          #+#    #+#             */
/*   Updated: 2024/10/02 00:22:15 by drabarza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (think(philo))
		return (NULL);
	if (philo->philo_id % 2 == 0)
		ft_usleep(50, philo);
		//ft_usleep((philo->info->time_to_die - philo->info->time_to_eat - philo->info->time_to_sleep) / 3, philo);
	while (1)
	{
		if (check_fork_availability(philo))
			return (NULL);
		if (eat(philo))
			return (NULL);
		if (ft_sleep(philo))
			return (NULL);
		if (think(philo))
			return (NULL);
	}
	return (NULL);
}
