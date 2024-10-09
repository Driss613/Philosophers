/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drabarza <drabarza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 13:50:27 by drabarza          #+#    #+#             */
/*   Updated: 2024/10/09 04:29:27 by drabarza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	stop_all_philo(t_philo *philo, int dead, int philo_id)
{
	t_philo	*tmp;
	int		time;

	if (dead)
		time = chronometer(0, philo);
	tmp = philo;
	while (tmp)
	{
		pthread_mutex_lock(&tmp->info->life_mutex);
		tmp->life = 0;
		pthread_mutex_unlock(&tmp->info->life_mutex);
		tmp = tmp->next;
	}
	if (dead && philo_id != -1)
	{
		pthread_mutex_lock(&philo->info->printf_mutex);
		printf("%d %d died\n", time, philo_id);
		pthread_mutex_unlock(&philo->info->printf_mutex);
	}
}

static int	check_and_stop_if_dead(t_philo *tmp, t_philo *philo)
{
	pthread_mutex_lock(&tmp->info->life_mutex);
	if (!tmp->life)
	{
		pthread_mutex_unlock(&tmp->info->life_mutex);
		stop_all_philo(philo, 1, tmp->philo_id);
		return (1);
	}
	pthread_mutex_unlock(&tmp->info->life_mutex);
	return (0);
}

static void	life_checker(t_philo *philo)
{
	t_philo	*tmp;
	int		i;

	while (1)
	{
		tmp = philo;
		i = 0;
		while (tmp)
		{
			if (check_and_stop_if_dead(tmp, philo))
				return ;
			pthread_mutex_lock(&tmp->info->satiated_mutex);
			if (tmp->satiated == 1)
				i++;
			pthread_mutex_unlock(&tmp->info->satiated_mutex);
			if (i == tmp->info->n_philos)
			{
				stop_all_philo(philo, 0, -1);
				return ;
			}
			tmp = tmp->next;
		}
		usleep(100);
	}
}

int	init_threads(t_info *info)
{
	t_philo	*current;

	current = info->philo;
	chronometer(1, info->philo);
	while (current)
	{
		if (pthread_create(&current->thread_id, NULL, (void *)routine, current))
		{
			printf("Error: Failed to create thread\n");
			return (1);
		}
		current = current->next;
	}
	life_checker(info->philo);
	current = info->philo;
	while (current)
	{
		if (pthread_join(current->thread_id, NULL))
		{
			printf("Error: Failed to join thread\n");
			return (1);
		}
		current = current->next;
	}
	return (0);
}
