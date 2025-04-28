/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdalal <rdalal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:41:18 by rdalal            #+#    #+#             */
/*   Updated: 2025/04/28 21:00:17 by rdalal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table		table;

	if (argc != 5 && argc != 6)
		return (printf("args missing\n"), 1);
	memset(&table, 0, sizeof(t_table));
	if (init_table(&table, argc, argv))
		return (1);
	if (start_threads(&table))
		return (cleanup(&table), 1);
	cleanup (&table);
	return (0);
}
