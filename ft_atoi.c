/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drabarza <drabarza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 18:48:37 by drabarza          #+#    #+#             */
/*   Updated: 2024/09/21 18:05:07 by drabarza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	arguments_is_valid(const char *nptr, long nbr, int sign, int i)
{
	if (nbr * sign < -2147483648 || nbr * sign > 2147483647)
		return (1);
	if (nptr[i] != '\0')
		return (1);
	if ((nptr[0] == '-' || nptr[0] == '+') && nptr[1] == '\0')
		return (1);
	return (0);
}

static void	calculint(const char *nptr, int i)
{
	int	countnumber;

	countnumber = 0;
	while (nptr[i] == '0')
		i++;
	while (nptr[i])
	{
		i++;
		countnumber++;
	}
	if (countnumber > 10)
	{
		printf("Error: The integer provided exceeds the maximum allowable value for an integer.\n");
		exit(0);
	}
}

int	ft_atoi(const char *nptr)
{
	long	nbr;
	int		sign;
	int		i;

	nbr = 0;
	sign = 1;
	i = 0;
	if (*nptr == '\0')
		return (-1);
	while ((nptr[i] >= '\t' && nptr[i] <= '\r') || nptr[i] == ' ')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	calculint(nptr, i);
	while (nptr[i] && (nptr[i] >= '0' && nptr[i] <= '9'))
	{
		nbr = 10 * nbr + (nptr[i] - 48);
		i++;
	}
	if (arguments_is_valid(nptr, nbr, sign, i))
		return (-1);
	return (nbr * sign);
}
