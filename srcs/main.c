/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdalal <rdalal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:41:18 by rdalal            #+#    #+#             */
/*   Updated: 2025/04/24 22:12:50 by rdalal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table		table;
	int			i;
	pthread_t	monitor;

	if ( argc != 5 && argc != 6)
		return (printf("args missing\n"), 1);
	if (init_table(&table, argc, argv))
		return (1);
	i = 0;
	while (i < table.nbr_philos)
	{
		if (pthread_create(&table.philos[i].thread, NULL, philo_life, &table.philos[i]))
			return (error_msg("thread not created"));
		i++;
	}
	if (pthread_create(&monitor, NULL, monitor_philo, &table))
		return (error_msg("monitor thread failed"));
	i = 0;
	while (i < table.nbr_philos)
		pthread_join(table.philos[i].thread, NULL);
	pthread_join(monitor, NULL);
	destroy_mutexes(&table);
	free(table.philos);
	free(table.forks);
	return (0);
}
