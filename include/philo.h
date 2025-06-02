/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadikaj <lsadikaj@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 11:00:44 by lsadikaj          #+#    #+#             */
/*   Updated: 2025/06/02 18:27:50 by lsadikaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>		// printf
# include <stdlib.h>	// malloc, free
# include <unistd.h>	// write, usleep
# include <stdbool.h>	
# include <pthread.h>	// mutex and threads 
# include <sys/time.h>	// gettimeofday
# include <limits.h>	// INT_MAX
# include <errno.h>

# define DEBUG_MODE	0

typedef enum e_mode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH
}	t_mode;

typedef enum e_time_code
{
	SECOND,
	MILLISECOND,
	MICROSECOND
}	t_time_code;

// enum pour l'état des philo
typedef enum e_philo_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED
}	t_philo_status;

/*
*	Code more readable
*/
typedef pthread_mutex_t	t_mtx;

// Pré-déclaration de structure
typedef struct s_table t_table;

/*
*  FORK
*/
typedef struct s_fork
{
	t_mtx	fork;
	int		fork_id;
}	t_fork;

/*
*  philo
*  ./philo 5 800 200 200 [5]
*/
typedef struct s_philo
{
	int			id;
	long		meals_counter;
	bool		full;
	long		last_meal_time;	// time passed from last meal
	t_fork		*first_fork;
	t_fork		*second_fork;
	pthread_t	thread_id;
	t_mtx		philo_mutex;	// useful for races with the monitor
	t_table		*table;         // Ajout d'un pointeur vers la table
}	t_philo;

/*
*	TABLE
*	./philo 5 800 200 200 [5]
*/
typedef struct s_table
{
	long		philo_nbr;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long		nbr_limit_meals;	// [5] or FLAG if -1 
	long		start_simulation;
	bool		end_simulation;		// a philo dies or all philos full
	bool		all_threads_ready;	// synchro philos
	long		threads_running_nbr;
	pthread_t	monitor;
	t_mtx		table_mutex;		// avoid races while reading from table
	t_mtx		write_mutex;
	t_fork		*forks;				// array
	t_philo		*philos;
}	t_table;

// PROTOTYPE

//utils
void		ft_exit(const char *error);
void		clean(t_table *table);
long		gettime(t_time_code time_code);
void		ft_usleep(long usec, t_table *table);
void		*ft_malloc(size_t bytes);
void		safe_mutex_handle(t_mtx *mutex, t_mode mode);
void		safe_thread_handle(pthread_t *thread, void *(*foo)(void *),
				void *data, t_mode mode);
bool		simulation_finished(t_table *table);
long		get_long(t_mtx *mutex, long  *value);
void 		set_long(t_mtx *mutex, long *dest, long value);
bool		get_bool(t_mtx *mutex, bool *value);
void		set_bool(t_mtx *mutex, bool *dest, bool value);
void		wait_all_threads(t_table *table);
bool		all_threads_are_running(t_mtx *mutex, long *threads,
				long philo_nbr);
void		increment_long(t_mtx *mutex, long *value);
void		de_synchronize_philos(t_philo *philo);
bool		all_threads_are_running(t_mtx *mutex, long *threads,
				long philo_nbr);
// dinner
void		thinking(t_philo *philo, bool pre_simulation);	
void		*lone_philo(void *arg);
void		*dinner_simulation(void *data);
void		dinner_start(t_table *table);
// monitor
void		*monitor_dinner(void *data);
// write
void		write_status(t_philo_status status, t_philo *philo, bool debug);

//parsing
void		parse_input(t_table *table, char **av);

//init
void		data_init(t_table *table);

//cleaning
void		clean(t_table *table);

#endif