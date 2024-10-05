/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drabarza <drabarza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 13:36:53 by drabarza          #+#    #+#             */
/*   Updated: 2024/10/01 13:37:18 by drabarza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
