/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drabarza <drabarza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 13:58:35 by drabarza          #+#    #+#             */
/*   Updated: 2024/10/05 09:15:23 by drabarza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_life(t_philo *philo)
{
	pthread_mutex_lock(&philo->life_mutex);
	if (!philo->life)
	{
		pthread_mutex_unlock(&philo->life_mutex);
		return (1);
	}
	if (chronometer(0, philo) - philo->last_eat >= philo->info->time_to_die)
	{
		philo->life = 0;
	}
	if (!philo->life)
	{
		pthread_mutex_unlock(&philo->life_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->life_mutex);
	return (0);
}

int	check_fork_availability(t_philo *philo)
{
	while (philo->number_of_fork < 2)
	{
		if (check_life(philo))
			return (1);
		pthread_mutex_lock(&philo->fork_mutex);
		if (philo->fork)
		{
			take_forks(philo, 0);
			philo->number_of_fork++;
		}
		pthread_mutex_unlock(&philo->fork_mutex);
		if (check_life(philo))
			return (1);
		pthread_mutex_lock(&philo->fork_mutex);
		if (*(philo->fork_right))
		{
			take_forks(philo, 1);
			philo->number_of_fork++;
		}
		pthread_mutex_unlock(&philo->fork_mutex);
		//usleep(100);
	}
	philo->number_of_fork = 0;
	return (0);
}

int	ft_sleep(t_philo *philo)
{
	int	start_sleep;

	start_sleep = chronometer(0, philo);
	if (check_life(philo))
		return (1);
	pthread_mutex_lock(&philo->printf_mutex);
	printf("%d %d is sleeping\n", start_sleep, philo->philo_id);
	pthread_mutex_unlock(&philo->printf_mutex);
	while (chronometer(0, philo) - start_sleep < philo->info->time_to_sleep)
	{
		if (check_life(philo))
		{
			return (0);
			sleep(50);
		}
	}
	if (!check_life(philo))
	{
		pthread_mutex_lock(&philo->printf_mutex);
		printf("%d %d is thinking\n", chronometer(0, philo), philo->philo_id);
		pthread_mutex_unlock(&philo->printf_mutex);
	}
	return (0);
}

int	eat(t_philo *philo)
{
	if (check_life(philo))
		return (1);
	philo->last_eat = chronometer(0, philo);
	pthread_mutex_lock(&philo->printf_mutex);
	printf("%d %d is eating\n", philo->last_eat, philo->philo_id);
	pthread_mutex_unlock(&philo->printf_mutex);
	philo->count_eat++;
	ft_time_to_eat(philo);
	pthread_mutex_lock(&philo->fork_mutex);
	philo->fork = 1;
	*(philo->fork_right) = 1;
	pthread_mutex_unlock(&philo->fork_mutex);
	return (0);
}

int	think(t_philo *philo)
{
	int	time;

	if (check_life(philo))
		return (1);
	time = chronometer(0, philo);
	pthread_mutex_lock(&philo->printf_mutex);
	printf("%d %d is thinking\n", time, philo->philo_id);
	pthread_mutex_unlock(&philo->printf_mutex);
	return (0);
}
