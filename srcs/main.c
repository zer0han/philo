/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdalal <rdalal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:41:18 by rdalal            #+#    #+#             */
/*   Updated: 2025/04/30 16:25:03 by rdalal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_loop(t_philo *philo)
{
	while (!check_stop(philo->table))
	{
		take_fork(philo);
		philo_eat(philo);
		pthread_mutex_lock(&philo->meal_mutex);
		if (philo->table->meals_required != -1 && \
			philo->meals_eaten >= philo->table->meals_required)
		{
			pthread_mutex_unlock(&philo->meal_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->meal_mutex);
		print_action(philo, "is sleeping");
		ft_sleep(philo->table->time_to_sleep, philo->table);
		print_action(philo, "is thinking");
	}
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->table->nbr_philos == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken a fork");
		ft_sleep(philo->table->time_to_die + 10, philo->table);
		return (NULL);
	}
	philo_loop(philo);
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_table		table;

	if (argc < 5 || argc > 6)
		return (printf("Wrong number of args\n"), 1);
	memset(&table, 0, sizeof(t_table));
	if (init_table(&table, argc, argv))
		return (1);
	if (start_threads(&table))
		return (cleanup(&table), 1);
	cleanup (&table);
	return (0);
}
