/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadikaj <lsadikaj@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 18:40:26 by lsadikaj          #+#    #+#             */
/*   Updated: 2025/06/17 15:13:59 by lsadikaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	write_status(t_philo_status status, t_philo *philo)
{
	long	elapsed;

	elapsed = gettime(MILLISECOND) - philo->table->start_simulation;
	if (philo->full)
		return ;
	safe_mutex_handle(&philo->table->write_mutex, LOCK);
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
	safe_mutex_handle(&philo->table->write_mutex, UNLOCK);
}
