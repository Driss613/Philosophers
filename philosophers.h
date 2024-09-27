/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drabarza <drabarza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 08:03:53 by drabarza          #+#    #+#             */
/*   Updated: 2024/09/27 16:56:00 by drabarza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>

typedef struct s_philo
{
	int				philo_id;
	int				fork;
	int				*fork_right;
	int				life;
	int				sleep;
	int				last_eat;
	pthread_mutex_t	life_mutex;
	pthread_mutex_t	fork_mutex;
	pthread_mutex_t	*fork_right_mutex;
	pthread_mutex_t	last_eat_mutex;
	pthread_mutex_t	printf_mutex;
	pthread_t		thread_id;
	struct s_philo	*next;
}	t_philo;

typedef struct s_info
{
	t_philo	*philo;
	int		number_of_philosophers;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		number_of_times_each_philosopher_must_eat;
}	t_info;

int	ft_atoi(const char *nptr);
#endif
