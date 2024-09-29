/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drabarza <drabarza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:33:49 by drabarza          #+#    #+#             */
/*   Updated: 2024/09/29 02:49:23 by drabarza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_value(int i, int value, t_info *info)
{
	if (i == 1)
		info->number_of_philosophers = value;
	else if (i == 2)
		info->time_to_die = value;
	else if (i == 3)
		info->time_to_eat = value;
	else if (i == 4)
	{
		info->time_to_sleep = value;
		info->number_of_times_each_philosopher_must_eat = 0;
	}
	else if (i == 5)
		info->number_of_times_each_philosopher_must_eat = value;
}

int	parsing(int argc, char **argv, t_info *info)
{
	int	i;
	int	value;

	i = 1;
	if (argc < 5 || argc > 6)
	{
		printf("Error: Wrong number of arguments. \
			Expected 5 or 6 arguments.\n");
		return (1);
	}
	while (argv[i])
	{
		value = ft_atoi(argv[i]);
		if (value <= 0)
		{
			printf("Error, The number must only be an integer \
				and must be positive\n");
			return (1);
		}
		init_value(i, value, info);
		value = 0;
		i++;
	}
	return (0);
}

t_philo	*ft_lstnew(int index, t_info *info)
{
	t_philo	*lst;

	lst = malloc(sizeof(t_philo));
	if (!lst)
		return (NULL);
	lst->info = info;
	lst->philo_id = index + 1;
	lst->info->life = 1;
	lst->fork = 1;
	lst->last_eat = 0;
	lst->sleep = 0;
	lst->number_of_fork = 0;
	lst->count_eat = 0;
	lst->fork_right = NULL;
	lst->info->philo_satiated = 0;
	lst->fork_right_mutex = malloc(sizeof(pthread_mutex_t));
	if (!lst->fork_right_mutex)
	{
		free(lst);
		return (NULL);
	}
	pthread_mutex_init(&lst->info->life_mutex, NULL);
	pthread_mutex_init(&lst->fork_mutex, NULL);
	pthread_mutex_init(lst->fork_right_mutex, NULL);
	pthread_mutex_init(&lst->info->philo_satiated_mutex, NULL);
	pthread_mutex_init(&lst->printf_mutex, NULL);
	lst->next = NULL;
	return (lst);
}

void	ft_lstadd_back(t_philo **lst, t_philo *newlst)
{
	t_philo	*head;

	if (!newlst || !lst)
		return ;
	if (!*lst)
	{
		*lst = newlst;
		return ;
	}
	head = *lst;
	while (head->next != NULL)
	{
		head = head->next;
	}
	head->next = newlst;
}

void	init_forks(t_info *info)
{
	int		i;
	t_philo	*philo;

	i = 1;
	philo = info->philo;
	while (info->number_of_philosophers > i)
	{
		philo->fork_right = &philo->next->fork;
		i++;
		philo = philo->next;
	}
	philo->fork_right = &info->philo->fork;
}

int	init_philo(t_info *info)
{
	int		i;
	t_philo	*tmp;

	i = 0;
	info->philo = NULL;
	while (info->number_of_philosophers > i)
	{
		tmp = ft_lstnew(i, info);
		if (!tmp)
		{
			printf("Error Allocation");
			return (1);
		}
		ft_lstadd_back(&info->philo, tmp);
		i++;
	}
	init_forks(info);
	return (0);
}

int	chronometer(int i, t_philo *philo)
{
	struct timeval	tv;
	int				time;

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
		return (time - philo->info->start_time);
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

int	check_life(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->life_mutex);
	if (!philo->info->life)
	{
		pthread_mutex_unlock(&philo->info->life_mutex);
		return (1);
	}
	if (chronometer(0, philo) - philo->last_eat >= philo->info->time_to_die)
	{
		philo->info->life = 0;
	}
	if (!philo->info->life)
	{
		pthread_mutex_unlock(&philo->info->life_mutex);
		pthread_mutex_lock(&philo->printf_mutex);
		printf("%d %d died\n", chronometer(0, philo), philo->philo_id);
		pthread_mutex_unlock(&philo->printf_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->info->life_mutex);
	return (0);
}

int	take_forks(t_philo *philo, int fork)
{
	if (check_life(philo))
		return (1);
	pthread_mutex_lock(&philo->printf_mutex);
	printf("%d %d has taken a fork\n", chronometer(0, philo), philo->philo_id);
	pthread_mutex_unlock(&philo->printf_mutex);
	if (fork == 0)
		philo->fork = 0;
	else
		*(philo->fork_right) = 0;
	return (0);
}

int	check_fork_availability(t_philo *philo)
{
	while (philo->number_of_fork < 2)
	{
		if (check_life(philo) || philo->info->philo_satiated == philo->info->number_of_philosophers)
			return (1);
		pthread_mutex_lock(&philo->fork_mutex);
		if (philo->fork)
		{
			take_forks(philo, 0);
			philo->number_of_fork++;
		}
		pthread_mutex_unlock(&philo->fork_mutex);
		if (check_life(philo) || philo->info->philo_satiated == philo->info->number_of_philosophers)
			return (1);
		pthread_mutex_lock(philo->fork_right_mutex);
		if (philo->fork_right)
		{
			take_forks(philo, 1);
			philo->number_of_fork++;
		}
		pthread_mutex_unlock(philo->fork_right_mutex);
		//usleep(100);
	}
	philo->number_of_fork = 0;
	return (0);
}

int	ft_sleep(t_philo *philo)
{
	int	start_sleep;

	if (check_life(philo))
		return (1);
	pthread_mutex_lock(&philo->printf_mutex);
	printf("%d %d is sleeping\n", chronometer(0, philo), philo->philo_id);
	pthread_mutex_unlock(&philo->printf_mutex);
	start_sleep = chronometer(0, philo);
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
		pthread_mutex_lock(&philo->info->philo_satiated_mutex);
		philo->info->philo_satiated++;
		pthread_mutex_unlock(&philo->info->philo_satiated_mutex);
	}
}

int	eat(t_philo *philo)
{
	if (check_life(philo))
		return (1);
	philo->last_eat = chronometer(0, philo);
	pthread_mutex_lock(&philo->printf_mutex);
	printf("%d %d is eating\n", chronometer(0, philo), philo->philo_id);
	pthread_mutex_unlock(&philo->printf_mutex);
	philo->count_eat++;
	ft_time_to_eat(philo);
	pthread_mutex_lock(&philo->fork_mutex);
	philo->fork = 1;
	pthread_mutex_unlock(&philo->fork_mutex);
	pthread_mutex_lock(philo->fork_right_mutex);
	*(philo->fork_right) = 1;
	pthread_mutex_unlock(philo->fork_right_mutex);
	return (0);
}

int	think(t_philo *philo)
{
	if (check_life(philo))
		return (1);
	pthread_mutex_lock(&philo->printf_mutex);
	printf("%d %d is thinking\n", chronometer(0, philo), philo->philo_id);
	pthread_mutex_unlock(&philo->printf_mutex);
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (think(philo))
		return (NULL);
	// voir pour commencer avec un think
	if (philo->philo_id % 2 == 0)
		ft_usleep(50, philo);
	while (1)
	{
		if (check_fork_availability(philo))
			return (NULL);
		if (philo->info->philo_satiated == philo->info->\
			number_of_philosophers || eat(philo))
			return (NULL);
		if (philo->info->philo_satiated == philo->info->\
			number_of_philosophers || ft_sleep(philo))
			return (NULL);
		if (philo->info->philo_satiated == philo->info->\
			number_of_philosophers || think(philo))
			return (NULL);
	}
	return (NULL);
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

void	free_philo(t_philo *philo)
{
	t_philo	*tmp;

	while (philo)
	{
		tmp = philo;
		philo = tmp->next;
		pthread_mutex_destroy(&tmp->info->life_mutex);
		pthread_mutex_destroy(&tmp->fork_mutex);
		pthread_mutex_destroy(tmp->fork_right_mutex);
		free(tmp->fork_right_mutex);
		pthread_mutex_destroy(&tmp->printf_mutex);
		free(tmp);
	}
}

/*void	print_info(t_info *info, int argc)
{
	printf("Number of philosophers: %d\n", info->number_of_philosophers);
	printf("time to die: %d\n", info->time_to_die);
	printf("Time to eat: %d\n", info->time_to_eat);
	printf("Time to sleep: %d\n", info->time_to_sleep);
	if (argc == 6)
		printf("Number of times each philosopher must eat: %d\n\n", \
			info->number_of_times_each_philosopher_must_eat);
	printf("\n\n");
}

void	print_philo(t_info *info)
{
	t_philo	*temp;

	temp = info->philo;
	while (temp)
	{
		printf("Philosopher ID: %d\n", temp->philo_id);
		printf("Fork: %d\n", temp->fork);
		printf("Fork Right: %p\n", (void*)temp->fork_right);
		printf("Life: %d\n", temp->life);
		printf("Sleep: %d\n", temp->sleep);
		printf("Last Eat: %d\n\n", temp->last_eat);
		temp = temp->next;
	}
}*/

int	main(int argc, char **argv)
{
	t_info	info;

	if (parsing(argc, argv, &info))
		return (0);
	if (init_philo(&info))
		return (0);
	if (init_threads(&info))
		return (0);
	//print_info(&info, argc);
	//print_philo(&info);
	free_philo(info.philo);
}
