/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drabarza <drabarza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 18:48:37 by drabarza          #+#    #+#             */
/*   Updated: 2024/10/09 03:17:45 by drabarza         ###   ########.fr       */
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

static int	calculint(const char *nptr, int i)
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
		return (1);
	return (0);
}

static void	check_sign(const char *nptr, int *i, int *sign)
{
	if (nptr[*i] == '-' || nptr[*i] == '+')
	{
		if (nptr[*i] == '-')
			*sign = -1;
		(*i)++;
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
	check_sign(nptr, &i, &sign);
	if (calculint(nptr, i))
		return (-1);
	while (nptr[i] && (nptr[i] >= '0' && nptr[i] <= '9'))
	{
		nbr = 10 * nbr + (nptr[i] - 48);
		i++;
	}
	if (arguments_is_valid(nptr, nbr, sign, i))
		return (-1);
	return (nbr * sign);
}
