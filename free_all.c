/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drabarza <drabarza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 13:43:03 by drabarza          #+#    #+#             */
/*   Updated: 2024/10/09 04:05:22 by drabarza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_all(t_info *info)
{
	t_philo	*tmp;
	if (info)
	{
		pthread_mutex_destroy(&info->life_mutex);
		pthread_mutex_destroy(&info->satiated_mutex);
		pthread_mutex_destroy(&info->printf_mutex);
	}
	while (info->philo)
	{
		tmp = info->philo;
		info->philo = tmp->next;
		pthread_mutex_destroy(&tmp->fork->mutex);
		free(tmp->fork);
		free(tmp);
	}
}
