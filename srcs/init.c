/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdalal <rdalal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:41:16 by rdalal            #+#    #+#             */
/*   Updated: 2025/04/17 16:22:36 by rdalal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_table(t_table *table, int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (1);
	table->nbr_philos = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	table->meals_required = -1;
	if (argc = 6)
		table->meals_required = ft_atoi(argv[5]);
	table->dead_philo = 0;
	table->start_time = get_time();
	return (0);
}

int	init_mutexes(t_table *table)
{
	
}

int	init_philos(t_table *table)
{
	
}
