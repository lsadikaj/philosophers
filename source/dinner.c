/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadikaj <lsadikaj@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:31:35 by lsadikaj          #+#    #+#             */
/*   Updated: 2025/05/15 17:31:00 by lsadikaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	thinking(t_philo *philo, bool pre_simulation)
{
	long	t_eat;
	long	t_sleep;
	long	t_think;

	if (!pre_simulation)
		write_status(THINKING, philo, DEBUG_MODE);
	// if the system is even we dont care, system already fair
	if (philo->table->philo_nbr % 2 == 0)
		return ;
	// not always fair
	t_eat = philo->table->time_to_eat;
	t_sleep = philo->table->time_to_sleep;
	t_think = t_eat * 2 - t_sleep;
	if (t_think < 0)
		t_think = 0;
	precise_usleep(t_think * 0.42, philo->table);
}

void	*lone_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_all_threads(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal_time,
				gettime(MILLISECOND));
	increase_long(&philo->table->table_mutex,
					&philo->table->threads_running_nbr);
	write_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
	while (!simulation_finished(philo->table))
		usleep(200);
	return (NULL);
}

static void	eat(t_philo *philo)
{
	safe_mutex_handle(&philo->first_fork->fork, LOCK);
	write_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
	safe_mutex_handle(&philo->second_fork->fork, LOCK);
	write_status(TAKE_SECOND_FORK, philo, DEBUG_MODE);

	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILLISECOND));
	philo->meals_counter++;
	write_status(EATING, philo, DEBUG_MODE);
	precise_usleep(philo->table->time_to_eat, philo->table);
	if (philo->table->nbr_limit_meals > 0
		&& philo->meals_counter == philo->table->nbr_limit_meals)
		set_bool(&philo->philo_mutex, &philo->full, true);
	safe_mutex_handle(&philo->first_fork->fork, UNLOCK);
	safe_mutex_handle(&philo->second_fork->fork, UNLOCK);
}


/*
*	wait all philos, synchro start
*	endless loop philo
*/
void	*dinner_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	// spinlock
	wait_all_threads(philo->table);
	// set time last meal
	set_long(&philo->philo_mutex, &philo->last_meal_time,
				gettime(MILLISECOND));
	// synchro with monitor
	// increase a table variable counter, with all threads runnning
	increase_long(&philo->table->table_mutex,
					&philo->table->threads_running_nbr);
	// desynchronize philos
	de_synchronize_philos(philo);
	while (!simulation_finished(philo->table))
	{
		// am i full
		if (philo->full)
			break ;
		// eat
		eat(philo);
		// sleep ->write_status & precise usleep
		write_status(SLEEPING, philo, DEBUG_MODE);
		precise_usleep(philo->table->time_to_sleep, philo->table);
		// think
		thinking(philo, false);
	}
	return (NULL);
}

/*
*	if no meals, return 0
*	if only one philo->ad hoc function
*	create all threads, all philos
*	create a monitor thread
*	synchronize the begginning of the simulation
*		pthread_create-> philo starts running
*		every philo start simultaneously
*	join everyone
*/
void	dinner_start(t_table *table)
{
	int	i;

	i = -1;
	if (table->nbr_limit_meals == 0)
		return ;
	else if (table->philo_nbr == 1)
		safe_thread_handle(&table->philos[0].thread_id, lone_philo,
							&table->philos[0], CREATE);
	else
	{
		while (++i < table->philo_nbr)
			safe_thread_handle(&table->philos[i].thread_id, dinner_simulation,
								&table->philos[i], CREATE);
	}
	// monitor
	safe_thread_handle(&table->monitor, monitor_dinner, table, CREATE);
	// start the simulation
	table->start_simulation = gettime(MILLISECOND);
	// now all threads are ready
	set_bool(&table->table_mutex, &table->all_threads_ready, true);
	// wait for everyone
	i = -1;
	while (++i < table->philo_nbr)
		safe_thread_handle(&table->philos[i].thread_id, NULL, NULL, JOIN);
	// if we reach this line, all philos are full
	set_bool(&table->table_mutex, &table->end_simulation, true);
	safe_thread_handle(&table->monitor, NULL, NULL, JOIN);
}