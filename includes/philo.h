/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdalal <rdalal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 17:38:27 by rdalal            #+#    #+#             */
/*   Updated: 2025/05/03 18:07:48 by rdalal           ###   ########.fr       */
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
# include <stdbool.h>
# include <limits.h>

# define TAKE_FORK "\x1b[38;2;144;238;144mhas taken a fork\x1b[0m"
# define EATING "\x1b[38;2;135;206;235mis eating\x1b[0m"
# define SLEEPING "\x1b[38;2;255;215;0mis sleeping\x1b[0m"
# define THINKING "\x1b[38;2;218;112;214mis thinking\x1b[0m"
# define DEAD "\x1b[38;2;251;73;52m is dead\x1b[0m"
# define MAX_PHILOS 200

/*structs*/

typedef struct s_table	t_table;

typedef struct s_philo
{
	int				id;
	long			last_meal_time;
	int				meals_eaten;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	meal_mutex;
	t_table			*table;
}					t_philo;

struct s_table
{
	int				nbr_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			time_to_think;
	int				meals_required;
	bool			stop;
	long			start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	stop_mutex;	
	t_philo			*philos;
};

/*functions*/

/**clean**/
void	cleanup(t_table *table);

/**utils**/
int		start_threads(t_table *table);
long	get_time(void);
void	ft_sleep(long duration, t_table *table);
void	*ft_memset(void *s, int c, size_t n);

/**utils2**/
int		ft_atoi(const char *str);
long	ft_atol(char *s);
bool	check_valid(char *str);

/**init**/
int		init_table(t_table *table, int argc, char **argv);
int		init_philos(t_table *table);
int		init_mutexes(t_table *table);

/**philo**/
void	print_action(t_philo *philo, char *msg);
bool	check_stop(t_table *table);
void	philo_eat(t_philo *philo);
int		take_fork(t_philo *philo);

/**watcher**/
void	*philo_routine(void *arg);
void	*monitor(void *arg);
#endif