/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdalal <rdalal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:41:16 by rdalal            #+#    #+#             */
/*   Updated: 2025/04/28 21:03:01 by rdalal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	valid_input(int argc, char **argv)
{
	int	i;

	i = 0;
	while (++i < argc)
	{
		if (ft_atoi(argv[i]) <= 0)
			return (1);
	}
	if (ft_atoi(argv[1]) > MAX_PHILOS)
	{
		printf("max philos exceeded (%d)\n", MAX_PHILOS);
		return (1);
	}
	return (0);
}

int	init_table(t_table *table, int argc, char **argv)
{
	if (valid_input(argc, argv))
		return (1);
	if (argc < 5 || argc > 6)
		return (1);
	table->nbr_philos = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	table->meals_required = -1;
	if (argc == 6)
		table->meals_required = ft_atoi(argv[5]);
	table->start_time = get_time();
	table->stop = false;
	if (init_mutexes(table))
		return (1);
	if (init_philos(table))
		return (1);
	return (0);
}

int	init_mutexes(t_table *table)
{
	int	i;

	i = 0;
	table->forks = malloc(sizeof(pthread_mutex_t) * table->nbr_philos);
	if (!table->forks)
		return (1);
	while (i < table->nbr_philos)
	{
		if (pthread_mutex_init(&table->forks[i], NULL))
			return (1);
		i++;
	}
	if (pthread_mutex_init(&table->print_mutex, NULL))
		return (1);
	if (pthread_mutex_init(&table->stop_mutex, NULL))
		return (1);
	return (0);
}

int	init_philos(t_table *table)
{
	int	i;

	i = 0;
	table->philos = malloc(sizeof(t_philo) * table->nbr_philos);
	if (!table->philos)
		return (1);
	while (i < table->nbr_philos)
	{
		table->philos[i].id = i + 1;
		table->philos[i].last_meal_time = table->start_time;
		table->philos[i].meals_eaten = 0;
		table->philos[i].left_fork = &table->forks[i];
		table->philos[i].right_fork = \
		&table->forks[(i + 1) % table->nbr_philos];
		table->philos[i].table = table;
		if (pthread_mutex_init(&table->philos[i].meal_mutex, NULL))
			return (1);
		i++;
	}
	return (0);
}
