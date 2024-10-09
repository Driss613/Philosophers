/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mutex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drabarza <drabarza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 03:10:02 by drabarza          #+#    #+#             */
/*   Updated: 2024/10/09 04:12:52 by drabarza         ###   ########.fr       */
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

t_fork	*ft_fork_init(void)
{
	t_fork	*lst;

	lst = malloc(sizeof(t_fork));
	if (!lst)
	{
		printf("Error Allocation\n");
		return (NULL);
	}
	lst->available = 1;
	if (pthread_mutex_init(&lst->mutex, NULL))
	{
		free(lst);
		printf("Error initializing mutex\n");
		return (NULL);
	}
	return (lst);
}
