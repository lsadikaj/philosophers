/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synchro_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadikaj <lsadikaj@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 18:07:57 by lsadikaj          #+#    #+#             */
/*   Updated: 2025/06/02 18:30:32 by lsadikaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/*
** Fonction d'attente active qui bloque jusqu'à ce que tous les threads soient prêts
** Permet de synchroniser le démarrage de tous les threads des philosophes
*/
void	wait_all_threads(t_table *table)
{
	while (!get_bool(&table->table_mutex, &table->all_threads_ready))
		;
}

/*
** Vérifie si tous les threads des philosophes sont en cours d'exécution
** Renvoie true si le nombre de threads en cours d'exécution est égal au nombre
** de philosophes
*/
bool	all_threads_are_running(t_mtx *mutex, long *threads, long philo_nbr)
{
	bool	ret;

	ret = false;
	safe_mutex_handle(mutex, LOCK);
	if (*threads == philo_nbr)
		ret = true;
	safe_mutex_handle(mutex, UNLOCK);
	return (ret);
}

/*
** Incrémente de manière thread-safe un compteur long
** Utilisé pour suivre le nombre de threads en cours d'exécution
*/
void	increment_long(t_mtx *mutex, long *value)
{
	safe_mutex_handle(mutex, LOCK);
	(*value)++;
	safe_mutex_handle(mutex, UNLOCK);
}

/*
** Désynchronise les philosophes pour rendre le système équitable
** Applique différentes stratégies selon que le nombre de philosophes est pair ou impair
*/
void	de_synchronize_philos(t_philo *philo)
{
	if (philo->table->philo_nbr % 2 == 0)
	{
		if (philo->id % 2 == 0)
			ft_usleep(3e4, philo->table);
	}
	else
	{
		if (philo->id % 2)
			thinking(philo, true);
	}
}
