/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drabarza <drabarza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 08:03:53 by drabarza          #+#    #+#             */
/*   Updated: 2024/09/29 02:49:46 by drabarza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				philo_id;
	int				fork;
	int				*fork_right;
	int				sleep;
	int				last_eat;
	int				count_eat;
	int				number_of_fork;
	pthread_mutex_t	fork_mutex;
	pthread_mutex_t	*fork_right_mutex;
	pthread_mutex_t	printf_mutex;
	pthread_t		thread_id;
	struct s_philo	*next;
	struct s_info	*info;
}	t_philo;

typedef struct s_info
{
	t_philo			*philo;
	int				start_time;
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				philo_satiated;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	int				life;
	pthread_mutex_t	life_mutex;
	pthread_mutex_t	philo_satiated_mutex;
}	t_info;

int	ft_atoi(const char *nptr);
#endif
