/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdalal <rdalal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:41:21 by rdalal            #+#    #+#             */
/*   Updated: 2025/04/28 21:03:21 by rdalal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(t_philo *philo, char *msg)
{
	long	time_stamp;

	pthread_mutex_lock(&philo->table->print_mutex);
	time_stamp = get_time() - philo->table->start_time;
	if (!check_stop(philo->table) || (strcmp(msg, DEAD) == 0))
		printf("%ld %d %s\n", time_stamp, philo->id, msg);
	pthread_mutex_unlock(&philo->table->print_mutex);
}

bool	check_stop(t_table *table)
{
	bool	stop;

	pthread_mutex_lock(&table->stop_mutex);
	stop = table->stop;
	pthread_mutex_unlock(&table->stop_mutex);
	return (stop);
}

int	take_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, TAKE_FORK);
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, TAKE_FORK);
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, TAKE_FORK);
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, TAKE_FORK);
	}
	return (0);
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal_time = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_mutex);
	print_action(philo, EATING);
	ft_sleep(philo->table->time_to_eat, philo->table);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}
