/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdalal <rdalal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 17:38:27 by rdalal            #+#    #+#             */
/*   Updated: 2025/04/24 21:45:47 by rdalal           ###   ########.fr       */
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


# define TAKE_FORK "has taken a fork"
# define EATING "is eating"
# define SLEEPING "is sleeping"
# define THINKING "is thinking"
# define DEAD "is dead"

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
	int				meal_count;
	int				stop_simulation;
	long			start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	meal_mutex;
	t_philo			*philos;
};

/*functions*/

/**clean**/
void	destroy_mutexes(t_table *table);
int		error_msg(char *msg);

/**utils**/
int		ft_atoi(const char *str);
long	get_time(void);
void	ft_sleep(long duration);
void	print_action(t_philo *philo, char *msg);

/**init**/
int		init_table(t_table *table, int argc, char **argv);
void	init_philos(t_table *table);
int		init_mutexes(t_table *table);

/**philo_life**/
void	*philo_life(void *arg);

/**philo**/
int		check_stop(t_table *table);
int		philo_eat(t_philo *philo);

/**watcher**/
int		check_death(t_philo *philo);
int		check_meal(t_table *table);
void	*monitor_philo(void *arg);
#endif