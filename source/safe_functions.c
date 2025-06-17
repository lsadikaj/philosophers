/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadikaj <lsadikaj@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 11:58:55 by lsadikaj          #+#    #+#             */
/*   Updated: 2025/06/17 15:03:21 by lsadikaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// Alloue de la mémoire de manière sécurisée
void	*ft_malloc(size_t bytes)
{
	void	*ret;
	
	ret = malloc(bytes);
	if (!ret)
		ft_exit("Error with malloc!");
	return (ret);
}

// Wrapper sécurisé pour les opérations mutex
void	safe_mutex_handle(t_mtx *mutex, t_mode mode)
{
	if (mode == LOCK)
		pthread_mutex_lock(mutex);
	else if (mode == UNLOCK)
		pthread_mutex_unlock(mutex);
	else if (mode == INIT)
		pthread_mutex_init(mutex, NULL);
	else if (mode == DESTROY)
		pthread_mutex_destroy(mutex);
	else
		ft_exit("Wrong mode for mutex handle!");
}


// Wrapper sécurisé pour les opérations thread
void	safe_thread_handle(pthread_t *thread, void *(*foo)(void *),
						void *data, t_mode mode)
{
	if (mode == CREATE)
		pthread_create(thread, NULL, foo, data);
	else if (mode == JOIN)
		pthread_join(*thread, NULL);
	else
		ft_exit("Wrong mode for thread_handle: use <CREATE> <JOIN>");
}
