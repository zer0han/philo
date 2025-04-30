/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdalal <rdalal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:35:03 by rdalal            #+#    #+#             */
/*   Updated: 2025/04/30 15:17:02 by rdalal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_digit(int i)
{
	if (i >= '0' && i <= '9')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	nb;
	int	sign;

	i = 0;
	nb = 0;
	sign = 1;
	while ((str[i] == '-') || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - 48);
		i++;
	}
	return (nb * sign);
}

long	ft_atol(char *s)
{
	long	result;
	int		sign;

	result = 0;
	sign = 1;
	while (*s == ' ' || (*s >= 9 && *s <= 13))
		s++;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
	while (is_digit(*s))
		result = result * 10 + (*s++ - '0');
	return (result * sign);
}

bool	check_valid(char *str)
{
	int		i;
	long	size;

	i = 0;
	if (str[0] == '-' || !str[i])
		return (false);
	while (str[i])
	{
		if (i > 10)
			return (false);
		if (!is_digit(str[i]))
			return (false);
		i++;
	}
	size = ft_atol(str);
	if (size > INT_MAX)
		return (false);
	return (true);
}
