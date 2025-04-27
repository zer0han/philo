/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdalal <rdalal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 21:04:15 by rdalal            #+#    #+#             */
/*   Updated: 2025/04/27 22:18:22 by rdalal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "philo.h"

// void	*philo_life(void *arg)
// {
// 	t_philo	*philo;

// 	philo = (t_philo *)arg;
// 	if (philo->id % 2 == 0)
// 		ft_sleep(10, philo->table);
// 	while (!check_stop(philo->table))
// 	{
// 		if (philo_eat(philo))
// 			break ;
// 		print_action(philo, SLEEPING);
// 		ft_sleep(philo->table->time_to_sleep, philo->table);
// 		print_action(philo, THINKING);
// 	}
// 	return (NULL);
// }