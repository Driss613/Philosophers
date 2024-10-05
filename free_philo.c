/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drabarza <drabarza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 13:43:03 by drabarza          #+#    #+#             */
/*   Updated: 2024/10/01 22:48:44 by drabarza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_philo(t_philo *philo)
{
	t_philo	*tmp;

	while (philo)
	{
		tmp = philo;
		philo = tmp->next;
		pthread_mutex_destroy(&tmp->life_mutex);
		pthread_mutex_destroy(&tmp->fork_mutex);
		//pthread_mutex_destroy(tmp->fork_right_mutex);
		//free(tmp->fork_right_mutex);
		pthread_mutex_destroy(&tmp->printf_mutex);
		pthread_mutex_destroy(tmp->info_mutex);
		free(tmp->info_mutex);
		free(tmp);
	}
}
