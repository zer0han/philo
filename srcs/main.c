/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdalal <rdalal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:41:18 by rdalal            #+#    #+#             */
/*   Updated: 2025/04/22 20:11:38 by rdalal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table		table;
	int			i;
	//pthread_t	moniter;

	if ( argc != 5 && argc != 6)
		return (printf("args missing: ./philo nbr_philo time_die \
			time_eat time_sleep [meals_required]\n"), 1);
	if (init_table(&table, argc, argv))
		return (1);
	init_mutexes(&table);
	init_philos(&table);
	i = 0;
	while (i < table.nbr_philos)
	{
		pthread_create(&table.philos[i].thread, NULL, philo_routine, &table.philos[i]);
		i++;
	}
	i = 0;
	while (i < table.nbr_philos)
	{
		pthread_join(table.philos[i].thread, NULL);
		i++;
	}
	pthread_join(table.philos[i++].thread, NULL);
	return (0);
}
