/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drabarza <drabarza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:05:17 by drabarza          #+#    #+#             */
/*   Updated: 2024/10/09 05:50:08 by drabarza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	take_forks(t_philo *philo, int fork)
{
	if (check_life(philo))
		return (1);
	pthread_mutex_lock(&philo->info->printf_mutex);
	printf("%d %d has taken a fork\n", chronometer(0, philo), philo->philo_id);
	pthread_mutex_unlock(&philo->info->printf_mutex);
	if (fork == 0)
		philo->fork->available = 0;
	else
		philo->fork_right->available = 0;
	return (0);
}

int	try_take_a_fork(t_philo *philo, int i, int *nb_of_fork)
{
	if (!i)
	{
		pthread_mutex_lock(&philo->fork->mutex);
		if (philo->fork->available)
		{
			if (take_forks(philo, 0))
				return (1);
			(*nb_of_fork)++;
		}
		pthread_mutex_unlock(&philo->fork->mutex);
	}
	else
	{
		pthread_mutex_lock(&philo->fork_right->mutex);
		if (philo->fork_right->available)
		{
			if (take_forks(philo, 1))
				return (1);
			(*nb_of_fork)++;
		}
		pthread_mutex_unlock(&philo->fork_right->mutex);
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
		result = time - philo->info->start_time;
		return (result);
	}
	return (0);
}

int	ft_usleep(int milliseconds, t_philo *philo)
{
	int	start;

	start = chronometer(0, philo);
	while ((chronometer(0, philo) - start) < milliseconds)
	{
		if (check_life(philo))
			return (1);
		usleep(500);
	}
	return (0);
}

int	ft_time_to_eat(t_philo *philo)
{
	if (ft_usleep(philo->info->time_to_eat, philo))
		return (1);
	if (philo->count_eat == philo->info->\
		number_of_times_each_philosopher_must_eat)
	{
		pthread_mutex_lock(&philo->info->satiated_mutex);
		philo->satiated++;
		pthread_mutex_unlock(&philo->info->satiated_mutex);
	}
	return (0);
}
