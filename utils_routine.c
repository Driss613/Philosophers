/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drabarza <drabarza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:05:17 by drabarza          #+#    #+#             */
/*   Updated: 2024/10/02 00:33:53 by drabarza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	take_forks(t_philo *philo, int fork)
{
	if (check_life(philo))
		return (1);
	pthread_mutex_lock(&philo->printf_mutex);
	printf("%d %d has taken a fork\n", chronometer(0, philo), philo->philo_id);
	pthread_mutex_unlock(&philo->printf_mutex);
	if (fork == 0)
	{
		//pthread_mutex_lock(&philo->printf_mutex);
		//printf("fork_before: %d %d\n", philo->fork, philo->philo_id);
		//pthread_mutex_unlock(&philo->printf_mutex);
		//philo->fork = 0;
		//pthread_mutex_lock(&philo->printf_mutex);
		//printf("fork_after: %d %d\n", philo->fork, philo->philo_id);
		//pthread_mutex_unlock(&philo->printf_mutex);
	}
	else
	{
		//pthread_mutex_lock(&philo->printf_mutex);
		//printf("fork_right before: %d %d\n", *(philo->fork_right), philo->philo_id);
		//pthread_mutex_unlock(&philo->printf_mutex);
		//*(philo->fork_right) = 0;
		//pthread_mutex_lock(&philo->printf_mutex);
		//printf("fork_right_after: %d %d\n", *(philo->fork_right), philo->philo_id);
		//pthread_mutex_unlock(&philo->printf_mutex);
	}
	return (0);
}

int	chronometer(int i, t_philo *philo)
{
	struct timeval	tv;
	int				time;
	int				result;

	if (i == 1)
	{
		gettimeofday(&tv, NULL);
		time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
		philo->info->start_time = time;
	}
	else
	{
		gettimeofday(&tv, NULL);
		time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
		pthread_mutex_lock(philo->info_mutex);
		result = time - philo->info->start_time;
		pthread_mutex_unlock(philo->info_mutex);
		return (result);
	}
	return (0);
}

int	ft_usleep(int milliseconds, t_philo *philo)
{
	int	start;

	start = chronometer(0, philo);
	while ((chronometer(0, philo) - start) < milliseconds)
		usleep(500);
	return (0);
}

void	ft_time_to_eat(t_philo *philo)
{
	while (chronometer(0, philo) - philo->last_eat < philo->info->time_to_eat)
	{
		if (check_life(philo))
		{
			ft_usleep(500, philo);
			break ;
		}
	}
	if (philo->count_eat == philo->info->\
		number_of_times_each_philosopher_must_eat)
	{
		pthread_mutex_lock(&philo->satiated_mutex);
		philo->satiated++;
		pthread_mutex_unlock(&philo->satiated_mutex);
	}
}
