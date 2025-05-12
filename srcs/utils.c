/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdalal <rdalal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:41:23 by rdalal            #+#    #+#             */
/*   Updated: 2025/05/03 19:57:12 by rdalal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

	(void)table;
	start = get_time();
	while ((get_time() - start) < duration)
		usleep(50);
}

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*str;

	i = 0;
	str = (unsigned char *)s;
	while (i < n)
	{
		str[i] = c;
		i++;
	}
	return (s);
}
