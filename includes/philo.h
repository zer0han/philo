/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdalal <rdalal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 17:38:27 by rdalal            #+#    #+#             */
/*   Updated: 2025/04/15 16:53:19 by rdalal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <strings.h>
# include <sys/time.h>
# include <pthread.h>


/*structs*/
typedef struct s_philo
{
	int					id;
	int					last_meal_time;
	int					meals_eaten;
	int					philo_nums;
	int					*dead;
	pthread_t			thread;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		*dead_lock;
	pthread_mutex_t		*meal_lock;
}						t_philo;

typedef struct s_table
{
	int				nbr_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_required;
	pthread_mutex_t	*forks;
	t_philo			*philos;
}					t_table;

/*functions*/


#endif