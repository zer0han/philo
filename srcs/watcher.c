/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdalal <rdalal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:16:38 by rdalal            #+#    #+#             */
/*   Updated: 2025/04/23 20:29:16 by rdalal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*moniter_philos(void *arg)
{
	t_table	*table;
	int		i;

	table = (t_table *)arg;
	while (1)
	{
		i = 0;
		while (i < table->nbr_philos)
		{
			pthread_mutex_lock(&table->death_mutex);
			if ((get_time() - table->philos[i].last_meal_time) > table->time_to_die)
			{
				print_action(&table->philos[i], "dead");
				table->dead_philo = 1;
				pthread_mutex_unlock(&table->death_mutex);
				return (NULL);
			}
			pthread_mutex_unlock(&table->death_mutex);
			i++;
		}
		pthread_mutex_lock(&table->meal_mutex);
		if (table->meals_required != -1 && table->philo_ate == table->nbr_philos)
		{
			printf("[debug] all ate lessgo bye bye\n");
			pthread_mutex_unlock(&table->meal_mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&table->meal_mutex);
		usleep(1000);
	}
}
