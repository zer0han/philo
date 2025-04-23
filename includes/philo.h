/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdalal <rdalal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 17:38:27 by rdalal            #+#    #+#             */
/*   Updated: 2025/04/23 19:27:51 by rdalal           ###   ########.fr       */
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
# include <semaphore.h>


/*structs*/

typedef struct s_table	t_table;

typedef struct s_philo
{
	int					id;
	long				last_meal_time;
	int					meals_eaten;
	pthread_t			thread;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		*dead_lock;
	pthread_mutex_t		*meal_lock;
	t_table				*table;
}						t_philo;

struct s_table
{
	int				nbr_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				meals_required;
	int				dead_philo;
	int				philo_ate;
	long			start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	meal_mutex;
	t_philo			*philos;
};

/*functions*/

/**utils**/
int		ft_atoi(const char *str);
long	get_time(void);
void	sleeps(long duration);
void	print_action(t_philo *philo, char *msg);

/**init**/
int		init_table(t_table *table, int argc, char **argv);
int		init_philos(t_table *table);
int		init_mutexes(t_table *table);

/**philo**/
void	*philo_routine(void *arg);

/**watcher**/
void	*moniter_philos(void *arg);
#endif