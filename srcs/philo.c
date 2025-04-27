/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdalal <rdalal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:41:21 by rdalal            #+#    #+#             */
/*   Updated: 2025/04/27 22:23:59 by rdalal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(t_philo *philo, char *msg)
{
	long	time_stamp;
	
	pthread_mutex_lock(&philo->table->print_mutex);
	time_stamp = get_time() - philo->table->start_time;
	if (!check_stop(philo->table))
		printf("%ld %d %s\n", time_stamp, philo->id, msg);
	pthread_mutex_unlock(&philo->table->print_mutex);
}

// void	print_action(t_philo *philo, char *msg)
// {
// 	long	time_stamp;
	
// 	pthread_mutex_lock(&philo->table->print_mutex);
// 	time_stamp = get_time() - philo->table->start_time;
// 	if (!philo->table->dead_philo)
// 		printf("%ld %d %s\n", time_stamp, philo->id, msg);
// 	pthread_mutex_unlock(&philo->table->print_mutex);
// }

bool	check_stop(t_table *table)
{
	bool	stop;

	pthread_mutex_lock(&table->stop_mutex);
	stop = table->stop;
	pthread_mutex_unlock(&table->stop_mutex);
	return (stop);
}

// int	check_stop(t_table *table)
// {
// 	int	stop;

// 	pthread_mutex_lock(&table->death_mutex);
// 	stop = table->stop_simulation;
// 	pthread_mutex_unlock(&table->death_mutex);
// 	return (stop);
// }

int	take_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, TAKE_FORK);
		if (check_stop(philo->table))
			return (pthread_mutex_unlock(philo->right_fork), 1);
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, TAKE_FORK);
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, TAKE_FORK);
		if (check_stop(philo->table))
			return (pthread_mutex_unlock(philo->left_fork), 1);
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, TAKE_FORK);
	}
	return (0);
}

void	philo_eat(t_philo *philo)
{
	if (take_fork(philo))
		return ;
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal_time = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_mutex);
	print_action(philo, EATING);
	ft_sleep(philo->table->time_to_eat, philo->table);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

// int	philo_eat(t_philo *philo)
// {
// 	t_table	*table;

// 	table = philo->table;
// 	pthread_mutex_lock(philo->left_fork);
// 	print_action(philo, TAKE_FORK);
// 	if (check_stop(table) || table->nbr_philos == 1)
// 		return (pthread_mutex_unlock(philo->left_fork), 1);
// 	pthread_mutex_lock(philo->right_fork);
// 	print_action(philo, TAKE_FORK);
// 	print_action(philo, EATING);
// 	pthread_mutex_lock(&table->death_mutex);
// 	philo->last_meal_time = get_time();
// 	pthread_mutex_unlock(&table->death_mutex);
// 	ft_sleep(table->time_to_eat, table);
// 	pthread_mutex_unlock(philo->left_fork);
// 	pthread_mutex_unlock(philo->right_fork);
// 	philo->meals_eaten++;
// 	if (philo->meals_eaten == table->meals_required)
// 	{
// 		pthread_mutex_lock(&table->death_mutex);
// 		table->meal_count++;
// 		pthread_mutex_unlock(&table->death_mutex);
// 	}
// 	return (check_stop(table));
// }
