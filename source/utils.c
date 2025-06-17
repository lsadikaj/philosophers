/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadikaj <lsadikaj@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 11:23:36 by lsadikaj          #+#    #+#             */
/*   Updated: 2025/06/17 15:12:23 by lsadikaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// Obtient le temps actuel dans l'unité spécifiée
long	gettime(t_second type)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		ft_exit("Gettimeofday failed.\n");
	if (type == SECOND)
		return (tv.tv_sec + (tv.tv_usec / 1e6));
	else if (type == MILLISECOND)
		return ((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
	else if (type == MICROSECOND)
		return ((tv.tv_sec * 1e6) + tv.tv_usec);
	else
		ft_exit("Wrong input to gettime.\n");
	return (1989);
}

// Version améliorée de usleep pour une attente plus précise
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

// Nettoie les ressources utilisées par le programme
void	ft_clean(t_table *table)
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

// Termine le programme proprement avec un message d'erreur
void	ft_exit(const char *error)
{
	printf("%s\n", error);
	exit(EXIT_FAILURE);
}
