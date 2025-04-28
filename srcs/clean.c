/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdalal <rdalal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:41:11 by rdalal            #+#    #+#             */
/*   Updated: 2025/04/28 19:52:23 by rdalal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	cleanup(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nbr_philos)
	{
		pthread_mutex_destroy(&table->forks[i]);
		pthread_mutex_destroy(&table->philos[i].meal_mutex);
		i++;
	}
	free(table->philos);
	free(table->forks);
	pthread_mutex_destroy(&table->print_mutex);
	pthread_mutex_destroy(&table->stop_mutex);
}

int	error_msg(char *msg)
{
	printf("%s\n", msg);
	return (1);
}
