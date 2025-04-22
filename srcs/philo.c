/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdalal <rdalal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:41:21 by rdalal            #+#    #+#             */
/*   Updated: 2025/04/22 20:28:10 by rdalal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (1)
	{
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken the fork");
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, "has taken the fork");
		pthread_mutex_lock(&philo->table->death_mutex);
		philo->last_meal_time = get_time();
		pthread_mutex_unlock(&philo->table->death_mutex);
		print_action(philo, "is eating");
		sleeps(philo->table->time_to_eat);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		philo->meals_eaten++;
		if (philo->table->meals_required != -1 && philo->meals_eaten >= philo->table->meals_required)
			break ;
		print_action(philo, "is sleeping");
		sleeps(philo->table->time_to_sleep);
		print_action(philo, "is thinking");
	}
	return (NULL);
}
