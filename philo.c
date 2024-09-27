/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drabarza <drabarza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:33:49 by drabarza          #+#    #+#             */
/*   Updated: 2024/09/27 16:56:14 by drabarza         ###   ########.fr       */
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
		info->time_to_sleep = value;
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
		printf("Error: Wrong number of arguments. Expected 5 or 6 arguments.\n");
		return (1);
	}
	while (argv[i])
	{
		value = ft_atoi(argv[i]);
		if (value <= 0)
		{
			printf("Error, The number must only be an integer and must be positive\n");
			return (1);
		}
		init_value(i, value, info);
		value = 0;
		i++;
	}
	return (0);
}

t_philo	*ft_lstnew(int index)
{
	t_philo	*lst;

	lst = malloc(sizeof(t_philo));
	if (!lst)
		return (NULL);
	lst->philo_id = index;
	lst->life = 1;
	lst->fork = 1;
	lst->last_eat = 0;
	lst->sleep = 0;
	lst->fork_right_mutex = malloc(sizeof(pthread_mutex_t));
	if (!lst->fork_right_mutex)
	{
		free(lst);
		return (NULL);
	}
	pthread_mutex_init(&lst->life_mutex, NULL);
	pthread_mutex_init(&lst->fork_mutex, NULL);
	pthread_mutex_init(lst->fork_right_mutex, NULL);
	pthread_mutex_init(&lst->last_eat_mutex, NULL);
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

	i = 0;
	philo = info->philo;
	while (info->number_of_philosophers - 1 > i)
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
		tmp = ft_lstnew(i);
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

int	check_life(t_philo *philo)
{
	pthread_mutex_lock(&philo->life_mutex);
	if (philo->life)
	{
		pthread_mutex_unlock(&philo->life_mutex);
		return (0);
	}
	pthread_mutex_unlock(&philo->life_mutex);
	return (1);
}

int	check_fork_availability(t_philo *philo)
{
	if (check_life(philo))
		return (1);
	pthread_mutex_lock(&philo->fork_mutex);
	if (philo->fork)
	{
		pthread_mutex_unlock(&philo->fork_mutex);
		pthread_mutex_lock(philo->fork_right_mutex);
		if (philo->fork_right)
		{
			pthread_mutex_unlock(philo->fork_right_mutex);
			//usleep(100); //! pas sur de l'avoir mis au bon endroit
			return (0);
		}
		return (1);
	}
	pthread_mutex_unlock(&philo->fork_mutex);
	return (1);
}

// il faudrais que je prenne la fourchette une fois disponnible

int	take_forks(t_philo *philo)
{
	if (check_life(philo))
		return (1);
	pthread_mutex_lock(&philo->fork_mutex);
	pthread_mutex_lock(&philo->printf_mutex);
	printf("Philosopher ID: %d has taken a fork\n", philo->philo_id);
	philo->fork = 0;
	pthread_mutex_unlock(&philo->fork_mutex);
	pthread_mutex_lock(philo->fork_right_mutex);
	printf("Philosopher ID: %d has taken a fork\n", philo->philo_id);
	*(philo->fork_right) = 0;
	pthread_mutex_unlock(philo->fork_right_mutex);
	return (0);
}

void	ft_sleep(t_philo *philo)
{
}

int	eat(t_philo *philo)
{
	if (check_life(philo))
		return (1);
	pthread_mutex_lock(&philo->last_eat_mutex);
	philo->last_eat += 50; 
	printf("Philosopher ID: %d is eating\n", philo->philo_id);
	pthread_mutex_unlock(&philo->last_eat_mutex);
	pthread_mutex_lock(&philo->fork_mutex);
	philo->fork = 1;
	pthread_mutex_unlock(&philo->fork_mutex);
	pthread_mutex_lock(philo->fork_right_mutex);
	*(philo->fork_right) = 1;
	pthread_mutex_unlock(philo->fork_right_mutex);
	//faire un ft_sleep
	ft_sleep(philo);
	return (0);
}

int	think(t_philo *philo)
{
	if (check_life(philo))
		return (1);
	//pthread_mutex_lock(&philo->printf_mutex);
	printf("Philosopher ID: %d is thinking\n", philo->philo_id);
	//pthread_mutex_unlock(&philo->printf_mutex);
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	// voir pour commencer avec un think
	if (philo->philo_id % 2 == 0)
		usleep(200);
	if (check_fork_availability(philo))
		return (NULL);
	if (take_forks(philo))
		return (NULL);
	if (eat(philo))
		return (NULL);
	if (think(philo))
		return (NULL);
	return (arg);
}

int	init_threads(t_info *info)
{
	t_philo	*current;

	current = info->philo;
	while (current)
	{
		if (pthread_create(&current->thread_id, NULL, routine, current))
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
		pthread_mutex_destroy(&tmp->life_mutex);
		pthread_mutex_destroy(&tmp->fork_mutex);
		pthread_mutex_destroy(tmp->fork_right_mutex);
		free(tmp->fork_right_mutex);
		pthread_mutex_destroy(&tmp->last_eat_mutex);
		pthread_mutex_destroy(&tmp->printf_mutex);
		free(tmp);
	}
}

void	print_info(t_info *info, int argc)
{
	printf("Number of philosophers: %d\n", info->number_of_philosophers);
	printf("time to die: %d\n", info->time_to_die);
	printf("Time to eat: %d\n", info->time_to_eat);
	printf("Time to sleep: %d\n", info->time_to_sleep);
	if (argc == 6)
		printf("Number of times each philosopher must eat: %d\n\n", info->number_of_times_each_philosopher_must_eat);
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
}

int	main(int argc, char **argv)
{
	t_info	info;

	if (parsing(argc, argv, &info))
		return (0);
	if (init_philo(&info))
		return (0);
	if (init_threads(&info))
		return (0);
	print_info(&info, argc);
	print_philo(&info);
	free_philo(info.philo);
}
