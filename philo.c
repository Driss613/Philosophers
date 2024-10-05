/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drabarza <drabarza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:33:49 by drabarza          #+#    #+#             */
/*   Updated: 2024/10/01 15:50:40 by drabarza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_info	info;

	if (parsing(argc, argv, &info))
		return (0);
	if (init_philo(&info))
	{
		free_philo(info.philo);
		return (0);
	}
	if (init_threads(&info))
		return (0);
	free_philo(info.philo);
}
