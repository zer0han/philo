/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdalal <rdalal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:16:38 by rdalal            #+#    #+#             */
/*   Updated: 2025/04/24 21:46:53 by rdalal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	*monitor_philos(void *arg)
// {
// 	t_table	*table;
// 	int		i;
// 	int		all_ate;

// 	table = (t_table *)arg;
// 	while (1)
// 	{
// 		i = 0;
// 		while (i < table->nbr_philos)
// 		{
// 			pthread_mutex_lock(&table->death_mutex);
// 			if ((get_time() - table->philos[i].last_meal_time) > table->time_to_die)
// 			{
// 				print_action(&table->philos[i], "dead");
// 				table->dead_philo = 1;
// 				pthread_mutex_unlock(&table->death_mutex);
// 				return (NULL);
// 			}
// 			i++;
// 			pthread_mutex_unlock(&table->death_mutex);
// 		}
// 		pthread_mutex_lock(&table->meal_mutex);
// 		if (table->meals_required != -1 && table->philo_ate == table->nbr_philos)
// 		{
// 			printf("[debug] all ate lessgo bye bye\n");
// 			pthread_mutex_unlock(&table->meal_mutex);
// 			return (NULL);
// 		}
// 		pthread_mutex_unlock(&table->meal_mutex);
// 		usleep(1000);
// 	}
// }

int	check_death(t_philo *philo)
{
	t_table	*table;
	long	time;

	table = philo->table;
	pthread_mutex_lock(&table->death_mutex);
	time = get_time() - philo->last_meal_time;
	if (time >= table->time_to_die)
	{
		table->stop_simulation = 1;
		pthread_mutex_unlock(&table->death_mutex);
		print_action(philo, DEAD);
		return (1);
	}
	pthread_mutex_unlock(&table->death_mutex);
	return (0);
}

int	check_meal(t_table *table)
{
	int	done;

	done = 0;
	if (table->meals_required == -1)
		return (0);
	pthread_mutex_lock(&table->meal_mutex);
	if (table->meal_count >= table->nbr_philos)
	{
		table->stop_simulation = 1;
		done = 1;
	}
	pthread_mutex_unlock(&table->meal_mutex);
	return (done);
}

void	*monitor_philo(void *arg)
{
	t_table	*table;
	int		i;

	table =(t_table *)arg;
	while (!check_stop(table))
	{
		i = 0;
		while (i < table->nbr_philos)
		{
			if (check_death(&table->philos[i]))
				return (NULL);
			i++;
		}
		if (check_meal(table))
		{
			pthread_mutex_lock(&table->print_mutex)	;
			printf("all ate\n");
			pthread_mutex_unlock(&table->print_mutex);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}