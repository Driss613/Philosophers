/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mutex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drabarza <drabarza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 03:10:02 by drabarza          #+#    #+#             */
/*   Updated: 2024/10/09 03:38:10 by drabarza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_mutex_info(t_info *info)
{
	if (pthread_mutex_init(&info->printf_mutex, NULL))
	{
		printf("Error initializing mutex\n");
		return (1);
	}
	if (pthread_mutex_init(&info->satiated_mutex, NULL))
	{
		printf("Error initializing mutex\n");
		return (1);
	}
	if (pthread_mutex_init(&info->life_mutex, NULL))
	{
		printf("Error initializing mutex\n");
		return (1);
	}
	return (0);
}

