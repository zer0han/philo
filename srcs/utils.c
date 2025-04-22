/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdalal <rdalal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:41:23 by rdalal            #+#    #+#             */
/*   Updated: 2025/04/22 20:09:12 by rdalal           ###   ########.fr       */
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
	return (nb *sign);
}

long	get_time(void)
{
	struct	timeval	tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	sleeps(long duration)
{
	long	start;

	start = get_time();
	while ((get_time() - start) < duration)
		usleep(100);
}

void	print_action(t_philo *philo, char *msg)
{
	long	time_stamp;
	
	pthread_mutex_lock(&philo->table->print_mutex);
	if (!philo->table->dead_philo)
	{
		time_stamp = get_time() - philo->table->start_time;
		printf("%ld %d %s\n", time_stamp, philo->id, msg);
	}
	pthread_mutex_unlock(&philo->table->print_mutex);
}
