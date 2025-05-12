/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdalal <rdalal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:16:38 by rdalal            #+#    #+#             */
/*   Updated: 2025/05/12 20:24:36 by rdalal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	check_meals(t_table *table)
{
	int	i;
	int	full_count;

	if (table->meals_required == -1)
		return (false);
	if (table->meals_required == 0)
		return (printf("it is done\n"), true);
	full_count = 0;
	i = -1;
	while (++i < table->nbr_philos)
	{
		pthread_mutex_lock(&table->philos[i].meal_mutex);
		if (table->philos[i].meals_eaten >= table->meals_required)
			full_count++;
		pthread_mutex_unlock(&table->philos[i].meal_mutex);
	}
	return (full_count == table->nbr_philos);
}

static bool	philo_death_check(t_table *table)
{
	int		i;
	long	time_since_meal;

	i = 0;
	while (i < table->nbr_philos)
	{
		pthread_mutex_lock(&table->philos[i].meal_mutex);
		time_since_meal = get_time() - table->philos[i].last_meal_time;
		pthread_mutex_unlock(&table->philos[i].meal_mutex);
		if (time_since_meal > table->time_to_die)
		{
			pthread_mutex_lock(&table->stop_mutex);
			if (!table->stop)
				table->stop = true;
			pthread_mutex_unlock(&table->stop_mutex);
			print_action(&table->philos[i], DEAD);
			return (true);
		}
		i++;
	}
	return (NULL);
}

void	*monitor(void *arg)
{
	t_table	*table;

	table = (t_table *)arg;
	while (!check_stop(table))
	{
		if (philo_death_check(table))
			return (NULL);
		if (check_meals(table))
		{
			pthread_mutex_lock(&table->stop_mutex);
			table->stop = true;
			pthread_mutex_unlock(&table->stop_mutex);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}
