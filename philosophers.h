/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drabarza <drabarza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 08:03:53 by drabarza          #+#    #+#             */
/*   Updated: 2024/10/02 01:17:00 by drabarza         ###   ########.fr       */
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
	int				life;
	int				satiated;
	pthread_mutex_t	life_mutex;
	pthread_mutex_t	satiated_mutex;
	pthread_mutex_t	fork_mutex;
	//pthread_mutex_t	*fork_right_mutex;
	pthread_mutex_t	printf_mutex;
	pthread_t		thread_id;
	pthread_mutex_t	*info_mutex;
	struct s_philo	*next;
	struct s_info	*info;
}	t_philo;

typedef struct s_info
{
	t_philo			*philo;
	int				start_time;
	int				n_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
}	t_info;

int		parsing(int argc, char **argv, t_info *info);
int		ft_atoi(const char *nptr);
int		init_philo(t_info *info);
void	init_value(int i, int value, t_info *info);
int		init_threads(t_info *info);
int		chronometer(int i, t_philo *philo);
void	*routine(void *arg);
int		check_life(t_philo *philo);
int		check_fork_availability(t_philo *philo);
int		think(t_philo *philo);
int		eat(t_philo *philo);
int		ft_sleep(t_philo *philo);
int		take_forks(t_philo *philo, int fork);
int		ft_usleep(int milliseconds, t_philo *philo);
void	ft_time_to_eat(t_philo *philo);
void	free_philo(t_philo *philo);
#endif
