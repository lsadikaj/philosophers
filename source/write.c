/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadikaj <lsadikaj@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 18:40:26 by lsadikaj          #+#    #+#             */
/*   Updated: 2025/05/29 14:39:16 by lsadikaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/*
** Affiche des messages de statut détaillés pour le mode debug
** Fournit des informations supplémentaires comme les IDs des fourchettes
** et le nombre de repas consommés
*/
static void	write_status_debug(t_philo_status status, t_philo *philo, long elapsed)
{
	if (status == TAKE_FIRST_FORK && !simulation_finished(philo->table))
		printf("%-6ld""%d has taken the first fork\n""no : %d\n", elapsed,
				philo->id, philo->first_fork->fork_id);
	else if (status == TAKE_SECOND_FORK && !simulation_finished(philo->table))
		printf("%-6ld""%d has taken the second fork\n""no : %d\n", elapsed,
				philo->id, philo->second_fork->fork_id);
	else if (status == EATING && !simulation_finished(philo->table))
		printf("%-6ld""%d is eating\n""meals no : %ld\n", elapsed, philo->id,
				philo->meals_counter);
	else if (status == SLEEPING && !simulation_finished(philo->table))
		printf("%-6ld""%d is sleeping\n", elapsed, philo->id);
	else if (status == THINKING && !simulation_finished(philo->table))
		printf("%-6ld""%d is thinking\n", elapsed, philo->id);
	else if (status == DIED)
		printf("%-6ld""%d died\n", elapsed, philo->id);
}

/*
** Fonction principale d'affichage des statuts des philosophes
** Protège l'affichage avec un mutex pour éviter les chevauchements
** Utilise le mode debug si activé, sinon affiche des messages standards
*/
void	write_status(t_philo_status status, t_philo *philo, bool debug)
{
	long	elapsed;

	elapsed = gettime(MILLISECOND) - philo->table->start_simulation;
	if (philo->full)
		return ;
	safe_mutex_handle(&philo->table->write_mutex, LOCK);
	if (debug)
		write_status_debug(status, philo, elapsed);
	else
	{
		if ((status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK)
			&& !simulation_finished(philo->table))
			printf("%-6ld""%d has taken a fork\n", elapsed, philo->id);
		else if (status == EATING && !simulation_finished(philo->table))
			printf("%-6ld""%d is eating\n", elapsed, philo->id);
		else if (status == SLEEPING && !simulation_finished(philo->table))
			printf("%-6ld""%d is sleeping\n", elapsed, philo->id);
		else if (status == THINKING && !simulation_finished(philo->table))
			printf("%-6ld""%d is thinking\n", elapsed, philo->id);
		else if (status == DIED)
			printf("%-6ld""%d died\n", elapsed, philo->id);
	}
	safe_mutex_handle(&philo->table->write_mutex, UNLOCK);
}
