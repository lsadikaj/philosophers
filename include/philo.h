/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadikaj <lsadikaj@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 11:00:44 by lsadikaj          #+#    #+#             */
/*   Updated: 2025/06/17 14:19:24 by lsadikaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>	
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
# include <errno.h>

// Type d'opérations à effectuer avec threads et mutex
typedef enum e_mode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
}	t_mode;

typedef enum e_second
{
	SECOND,
	MILLISECOND,
	MICROSECOND
}	t_second;

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


typedef pthread_mutex_t	t_mtx;
typedef struct s_table t_table;

typedef struct s_fork
{
	t_mtx	fork;
	int		fork_id;
}	t_fork;

// Structure pour un philo
typedef struct s_philo
{
	int			id;
	long		meals_counter;
	bool		full;
	long		last_meal_time;	
	t_fork		*first_fork;
	t_fork		*second_fork;
	pthread_t	thread_id;
	t_mtx		philo_mutex;
	t_table		*table;
}	t_philo;

// Structure globale
typedef struct s_table
{
	long		philo_nbr;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long		nbr_limit_meals;
	long		start_simulation;
	bool		end_simulation;
	bool		all_threads_ready;
	long		threads_running_nbr;
	pthread_t	monitor;
	t_mtx		table_mutex;
	t_mtx		write_mutex;
	t_fork		*forks;
	t_philo		*philos;
}	t_table;

// PROTOTYPE
void		ft_exit(const char *error);
void		ft_clean(t_table *table);
long		gettime(t_second type);
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
void		thinking(t_philo *philo, bool pre_simulation);	
void		*lone_philo(void *arg);
void		*simulation(void *data);
void		simulation_start(t_table *table);
void		*monitor_simulation(void *data);
void		write_status(t_philo_status status, t_philo *philo);
void		parse_input(t_table *table, char **av);
void		data_init(t_table *table);
void		ft_clean(t_table *table);

#endif