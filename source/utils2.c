/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadikaj <lsadikaj@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:55:22 by lsadikaj          #+#    #+#             */
/*   Updated: 2025/05/19 17:47:39 by lsadikaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/*
** Définit une valeur booléenne de manière thread-safe
** Utilise un mutex pour protéger l'accès à la variable partagée
*/
void	set_bool(t_mtx *mutex, bool *dest, bool value)
{
	safe_mutex_handle(mutex, LOCK);
	*dest = value;
	safe_mutex_handle(mutex, UNLOCK);
}

/*
** Récupère une valeur booléenne de manière thread-safe
** Utilise un mutex pour protéger l'accès à la variable partagée
*/
bool	get_bool(t_mtx *mutex, bool *value)
{
	bool	ret;

	safe_mutex_handle(mutex, LOCK);
	ret = *value;
	safe_mutex_handle(mutex, UNLOCK);
	return (ret);
}

/*
** Définit une valeur long de manière thread-safe
** Utilise un mutex pour protéger l'accès à la variable partagée
*/
void	set_long(t_mtx *mutex, long *dest, long value)
{
	safe_mutex_handle(mutex, LOCK);
	*dest = value;
	safe_mutex_handle(mutex, UNLOCK);
}

/*
** Récupère une valeur long de manière thread-safe
** Utilise un mutex pour protéger l'accès à la variable partagée
*/
long	get_long(t_mtx *mutex, long *value)
{
	long	ret;

	safe_mutex_handle(mutex, LOCK);
	ret = *value;
	safe_mutex_handle(mutex, UNLOCK);
	return (ret);
}

/*
** Vérifie si la simulation est terminée
** Renvoie l'état actuel du drapeau end_simulation
*/
bool	simulation_finished(t_table *table)
{
	return (get_bool(&table->table_mutex, &table->end_simulation));
}
