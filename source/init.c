/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadikaj <lsadikaj@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 11:56:41 by lsadikaj          #+#    #+#             */
/*   Updated: 2025/06/02 18:28:03 by lsadikaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/*
** Assigne les fourchettes à un philosophe
** Attribue les fourchettes gauche et droite en fonction de la position
** Les philosophes pairs et impairs reçoivent les fourchettes dans un ordre différent
** pour éviter les deadlocks
*/
static void	assign_forks(t_philo *philo, t_fork *forks, int philo_position)
{
	int	philo_nbr;

	philo_nbr = philo->table->philo_nbr;
	philo->first_fork = &forks[(philo_position + 1) % philo_nbr];
	philo->second_fork = &forks[philo_position];
	if (philo->id % 2 == 0)
	{
		philo->first_fork = &forks[philo_position];
		philo->second_fork = &forks[(philo_position + 1) % philo_nbr];
	}
}

/*
** Initialise tous les philosophes
** Configure les attributs de base et assigne les fourchettes à chaque philosophe
*/
static void	philo_init(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while (++i < table->philo_nbr)
	{
		philo = table->philos + i;
		philo->id = i + 1;
		philo->full = false;
		philo->meals_counter = 0;
		philo->table = table;
		safe_mutex_handle(&philo->philo_mutex, INIT);
		assign_forks(philo, table->forks, i);
	}
}

/*
** Initialise toutes les données nécessaires à la simulation
** 1. Configure les drapeaux de la table
** 2. Initialise les mutex de la table
** 3. Alloue la mémoire pour les philosophes et les fourchettes
** 4. Initialise les fourchettes et les philosophes
*/
void	data_init(t_table *table)
{
	int	i;

	i = -1;
	table->end_simulation = false;
	table->all_threads_ready = false;
	table->threads_running_nbr = 0;
	safe_mutex_handle(&table->table_mutex, INIT);
	safe_mutex_handle(&table->write_mutex, INIT);
	table->philos = ft_malloc(sizeof(t_philo) * table->philo_nbr);
	table->forks = ft_malloc(sizeof(t_fork) * table->philo_nbr);
	while (++i < table->philo_nbr)
	{
		safe_mutex_handle(&table->forks[i].fork, INIT);
		table->forks[i].fork_id = i;
	}
	philo_init(table);
}
