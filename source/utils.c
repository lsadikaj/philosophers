/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadikaj <lsadikaj@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 11:23:36 by lsadikaj          #+#    #+#             */
/*   Updated: 2025/06/02 18:31:31 by lsadikaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/*
** Obtient le temps actuel dans l'unité spécifiée
** Supporte les secondes, millisecondes et microsecondes
** Utilise gettimeofday pour obtenir le temps avec précision
*/
long	gettime(t_time_code time_code)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		ft_exit("Gettimeofday failed.\n");
	if (time_code == SECOND)
		return (tv.tv_sec + (tv.tv_usec / 1e6));
	else if (time_code == MILLISECOND)
		return ((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
	else if (time_code == MICROSECOND)
		return ((tv.tv_sec * 1e6) + tv.tv_usec);
	else
		ft_exit("Wrong input to gettime.\n");
	return (1989);
}

/*
** Version améliorée de usleep pour une attente plus précise
** Utilise une combinaison d'usleep et d'attente active pour
** obtenir une précision maximale, surtout sur les petits délais
*/
void	ft_usleep(long usec, t_table *table)
{
	long	start;
	long	elapsed;
	long	rem;

	start = gettime(MICROSECOND);
	while (gettime(MICROSECOND) - start < usec)
	{
		if (simulation_finished(table))
			break ;
		elapsed = gettime(MICROSECOND) - start;
		rem = usec - elapsed;
		if (rem > 1e3)
			usleep(rem / 2);
		else
		{
			while (gettime(MICROSECOND) - start < usec)
				;
		}
	}
}

/*
** Nettoie les ressources utilisées par le programme
** Détruit tous les mutex et libère la mémoire allouée
*/
void	clean(t_table *table)
{
	t_philo	*philo;
	int		i;

	i = -1;
	while (++i < table->philo_nbr)
	{
		philo = table->philos + i;
		safe_mutex_handle(&philo->philo_mutex, DESTROY);
	}
	safe_mutex_handle(&table->write_mutex, DESTROY);
	safe_mutex_handle(&table->table_mutex, DESTROY);
	free(table->forks);
	free(table->philos);
}

/*
** Termine le programme proprement avec un message d'erreur
** Affiche le message donné puis quitte avec un code d'erreur
*/
void	ft_exit(const char *error)
{
	printf("%s\n", error);
	exit(EXIT_FAILURE);
}
