/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drabarza <drabarza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:33:49 by drabarza          #+#    #+#             */
/*   Updated: 2024/10/09 04:23:10 by drabarza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_info	info;

	if (parsing(argc, argv, &info))
		return (0);
	if (init_mutex_info(&info))
	{
		free_all(&info);
		return (1);
	}
	if (init_philo(&info))
	{
		free_all(&info);
		return (0);
	}
	if (init_threads(&info))
	{
		free_all(&info);
		return (0);
	}
	free_all(&info);
	return (1);
}
