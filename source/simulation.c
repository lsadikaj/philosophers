/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadikaj <lsadikaj@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:31:35 by lsadikaj          #+#    #+#             */
/*   Updated: 2025/06/02 18:30:27 by lsadikaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/*
** Gère la réflexion du philosophe et calcule le temps de réflexion optimal
** pour assurer une distribution équitable du temps de parole
** Le temps de réflexion est calculé en fonction du temps pour manger et dormir
*/
void	thinking(t_philo *philo, bool pre_simulation)
{
	long	t_eat;
	long	t_sleep;
	long	t_think;

	if (!pre_simulation)
		write_status(THINKING, philo, DEBUG_MODE);
	if (philo->table->philo_nbr % 2 == 0)
		return ;
	t_eat = philo->table->time_to_eat;
	t_sleep = philo->table->time_to_sleep;
	t_think = t_eat * 2 - t_sleep;
	if (t_think < 0)
		t_think = 0;
	ft_usleep(t_think * 0.42, philo->table);
}

/*
** Routine pour un philosophe solitaire qui ne peut jamais manger
** Il prend une fourchette et attend indéfiniment jusqu'à la fin de la simulation
*/
void	*lone_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_all_threads(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal_time,
				gettime(MILLISECOND));
	increment_long(&philo->table->table_mutex,
					&philo->table->threads_running_nbr);
	write_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
	while (!simulation_finished(philo->table))
		usleep(200);
	return (NULL);
}

/*
** Processus de repas d'un philosophe
** 1. Prendre les deux fourchettes
** 2. Manger pendant time_to_eat millisecondes
** 3. Relâcher les fourchettes
*/
static void	eat(t_philo *philo)
{
	safe_mutex_handle(&philo->first_fork->fork, LOCK);
	write_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
	safe_mutex_handle(&philo->second_fork->fork, LOCK);
	write_status(TAKE_SECOND_FORK, philo, DEBUG_MODE);

	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILLISECOND));
	philo->meals_counter++;
	write_status(EATING, philo, DEBUG_MODE);
	ft_usleep(philo->table->time_to_eat, philo->table);
	if (philo->table->nbr_limit_meals > 0
		&& philo->meals_counter == philo->table->nbr_limit_meals)
		set_bool(&philo->philo_mutex, &philo->full, true);
	safe_mutex_handle(&philo->first_fork->fork, UNLOCK);
	safe_mutex_handle(&philo->second_fork->fork, UNLOCK);
}

/*
** Routine principale d'un philosophe
** 1. Attendre que tous les threads soient prêts
** 2. Initialiser son temps de dernier repas
** 3. Boucle de vie: manger, dormir, penser
** 4. Termine quand la simulation est finie ou le philosophe est rassasié
*/
void	*dinner_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal_time,
				gettime(MILLISECOND));
	increment_long(&philo->table->table_mutex,
					&philo->table->threads_running_nbr);
	de_synchronize_philos(philo);
	while (!simulation_finished(philo->table))
	{
		if (philo->full)
			break ;
		eat(philo);
		write_status(SLEEPING, philo, DEBUG_MODE);
		ft_usleep(philo->table->time_to_sleep, philo->table);
		thinking(philo, false);
	}
	return (NULL);
}

/*
** Initialise et démarre la simulation du dîner des philosophes
** 1. Crée un thread pour chaque philosophe (cas spécial pour un philosophe)
** 2. Crée un thread de surveillance
** 3. Initialise la simulation et attend que tous les threads soient prêts
** 4. Attend la fin de tous les threads et nettoie les ressources
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
	safe_thread_handle(&table->monitor, monitor_dinner, table, CREATE);
	table->start_simulation = gettime(MILLISECOND);
	set_bool(&table->table_mutex, &table->all_threads_ready, true);
	i = -1;
	while (++i < table->philo_nbr)
		safe_thread_handle(&table->philos[i].thread_id, NULL, NULL, JOIN);
	set_bool(&table->table_mutex, &table->end_simulation, true);
	safe_thread_handle(&table->monitor, NULL, NULL, JOIN);
}
