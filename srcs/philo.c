/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdalal <rdalal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:41:21 by rdalal            #+#    #+#             */
/*   Updated: 2025/04/24 21:29:50 by rdalal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


// void	*philo_routine(void *arg)
// {
// 	t_philo	*philo;

// 	philo = (t_philo *)arg;
// 	if (philo->id % 2 == 0)
// 		usleep(1000);
// 	while (1)
// 	{
// 		pthread_mutex_lock(philo->left_fork);
// 		print_action(philo, "has taken the fork");
// 		pthread_mutex_lock(philo->right_fork);
// 		print_action(philo, "has taken the fork");
// 		pthread_mutex_lock(&philo->table->death_mutex);
// 		philo->last_meal_time = get_time();
// 		pthread_mutex_unlock(&philo->table->death_mutex);
// 		print_action(philo, "is eating");
// 		ft_sleep(philo->table->time_to_eat);
// 		pthread_mutex_lock(&philo->table->meal_mutex);
// 		philo->meals_eaten++;
// 		if (philo->table->meals_required != -1 && philo->meals_eaten >= philo->table->meals_required)
// 			philo->table->philo_ate++;
// 		pthread_mutex_unlock(&philo->table->meal_mutex);
// 		pthread_mutex_unlock(philo->left_fork);
// 		pthread_mutex_unlock(philo->right_fork);
// 		print_action(philo, "is sleeping");
// 		ft_sleep(philo->table->time_to_sleep);
// 		print_action(philo, "is thinking");
// 	}
// 	return (NULL);
// }

int	check_stop(t_table *table)
{
	int	stop;

	pthread_mutex_lock(&table->death_mutex);
	stop = table->stop_simulation;
	pthread_mutex_unlock(&table->death_mutex);
	return (stop);
}

int	philo_eat(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	pthread_mutex_lock(philo->left_fork);
	print_action(philo, TAKE_FORK);
	if (table->nbr_philos == 1)
	{
		ft_sleep(table->time_to_die + 10);
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	pthread_mutex_lock(philo->right_fork);
	print_action(philo, TAKE_FORK);
	print_action(philo, EATING);
	pthread_mutex_lock(&table->death_mutex);
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(&table->death_mutex);
	ft_sleep(table->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	philo->meals_eaten++;
	if (philo->meals_eaten == table->meals_required)
	{
		pthread_mutex_lock(&table->death_mutex);
		table->meal_count++;
		pthread_mutex_unlock(&table->death_mutex);
	}
	return (0);
}
