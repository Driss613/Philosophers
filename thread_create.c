/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drabarza <drabarza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 13:50:27 by drabarza          #+#    #+#             */
/*   Updated: 2024/10/01 22:03:36 by drabarza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* func stop (tous les philos, le philo mort)
	boucle sur tous les philos
		met life a 0
		
	tu fait le message de mort
 */

/*  func checker
	boucle sur tous les philos tant qu'ils tournent
		est ce au'il est mort?
		-> si oui: tu stop les autres -> appelle func stop;
		si ils ont tous manger
		-> si oui: tu stop les philos
 */

void	stop_all_philo(t_philo *philo, int dead)
{
	t_philo	*tmp;
	int		time;

	if (dead)
		time = chronometer(0, philo);
	tmp = philo;
	while (philo)
	{
		pthread_mutex_lock(&philo->life_mutex);
		philo->life = 0;
		pthread_mutex_unlock(&philo->life_mutex);
		philo = philo->next;
	}
	philo = tmp;
	if (dead)
	{
		pthread_mutex_lock(&philo->printf_mutex);
		printf("%d %d died\n", time, philo->philo_id);
		pthread_mutex_unlock(&philo->printf_mutex);
	}
}

void	life_checker(t_philo *philo)
{
	t_philo	*tmp;
	int		i;

	while (1)
	{
		tmp = philo;
		i = 0;
		while (philo)
		{
			pthread_mutex_lock(&philo->life_mutex);
			if (!philo->life)
			{
				pthread_mutex_unlock(&philo->life_mutex);
				stop_all_philo(philo, 1);
				return ;
			}
			pthread_mutex_unlock(&philo->life_mutex);
			pthread_mutex_lock(&philo->satiated_mutex);
			if (philo->satiated == 1)
				i++;
			pthread_mutex_unlock(&philo->satiated_mutex);
			pthread_mutex_lock(philo->info_mutex);
			if (i == philo->info->n_philos)
			{
				pthread_mutex_unlock(philo->info_mutex);
				stop_all_philo(philo, 0);
				return ;
			}
			pthread_mutex_unlock(philo->info_mutex);
			tmp = philo->next;
		}
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
	// func checker
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
