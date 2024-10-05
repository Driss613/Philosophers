/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drabarza <drabarza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 13:31:41 by drabarza          #+#    #+#             */
/*   Updated: 2024/10/02 01:16:58 by drabarza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_value(int i, int value, t_info *info)
{
	if (i == 1)
		info->n_philos = value;
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

static t_philo	*ft_lstnew(int index, t_info *info)
{
	t_philo	*lst;

	lst = malloc(sizeof(t_philo));
	if (!lst)
		return (NULL);
	lst->info = info;
	lst->philo_id = index + 1;
	lst->life = 1;
	lst->fork = 1;
	lst->last_eat = 0;
	lst->sleep = 0;
	lst->number_of_fork = 0;
	lst->count_eat = 0;
	lst->satiated = 0;
	lst->fork_right = malloc(sizeof(int));
	if (!lst->fork_right)
	{
		free(lst);
		return (NULL);
	}
	//lst->fork_right_mutex = malloc(sizeof(pthread_mutex_t));
	/*if (!lst->fork_right_mutex)
	{
		free(lst);
		free(lst->fork_right);
		return (NULL);
	}*/
	lst->info_mutex = malloc(sizeof(pthread_mutex_t));
	if (!lst->info_mutex)
	{
		free(lst);
		free(lst->fork_right);
		//free(lst->fork_right_mutex);
		return (NULL);
	}
	pthread_mutex_init(&lst->life_mutex, NULL);
	pthread_mutex_init(&lst->fork_mutex, NULL);
	//pthread_mutex_init(lst->fork_right_mutex, NULL);
	pthread_mutex_init(&lst->satiated_mutex, NULL);
	pthread_mutex_init(&lst->printf_mutex, NULL);
	pthread_mutex_init(lst->info_mutex, NULL);
	lst->next = NULL;
	return (lst);
}

static void	init_forks(t_info *info)
{
	int		i;
	t_philo	*philo;

	i = 1;
	philo = info->philo;
	if (info->n_philos == 1)
	{
		philo->fork_right = NULL;
		return ;
	}
	while (info->n_philos > i)
	{
		philo->fork_right = &philo->next->fork;
		i++;
		philo = philo->next;
	}
	philo->fork_right = &info->philo->fork;
}

static void	ft_lstadd_back(t_philo **lst, t_philo *newlst)
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

int	init_philo(t_info *info)
{
	int		i;
	t_philo	*tmp;

	i = 0;
	info->philo = NULL;
	while (info->n_philos > i)
	{
		tmp = ft_lstnew(i, info);
		if (!tmp)
		{
			printf("Error Allocation\n");
			return (1);
		}
		ft_lstadd_back(&info->philo, tmp);
		i++;
	}
	init_forks(info);
	return (0);
}
