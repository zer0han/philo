/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdalal <rdalal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:41:23 by rdalal            #+#    #+#             */
/*   Updated: 2025/04/28 21:01:28 by rdalal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	start_threads(t_table *table)
{
	int			i;
	pthread_t	monitor_th;

	i = 0;
	while (i < table->nbr_philos)
	{
		if (pthread_create(&table->philos[i].thread, NULL, \
			philo_routine, &table->philos[i]))
			return (1);
		i++;
	}
	if (pthread_create(&monitor_th, NULL, monitor, table))
		return (1);
	i = 0;
	while (i < table->nbr_philos)
	{
		pthread_join(table->philos[i].thread, NULL);
		i++;
	}
	pthread_join(monitor_th, NULL);
	return (0);
}

void	ft_sleep(long duration, t_table *table)
{
	long	start;

	start = get_time();
	while (!check_stop(table) && (get_time() - start) < duration)
		usleep(100);
}
