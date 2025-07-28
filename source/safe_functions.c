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

// Check le resultat après un appel aux fonction système
static void	check_result(int result, const char *operation)
{
	if (result != 0)
	{
		printf("Error: %s failed with code %d", operation, result);
		exit(EXIT_FAILURE);
	}
}

// Wrapper sécurisé pour les opérations mutex
void	safe_mutex_handle(t_mtx *mutex, t_mode mode)
{
	int	result;

	result = 0;
	if (mode == LOCK)
	{
		result = pthread_mutex_lock(mutex);
		check_result(result, "pthread_mutex_lock");
	}
	else if (mode == UNLOCK)
	{
		result = pthread_mutex_unlock(mutex);
		check_result(result, "pthread_mutex_unlock");
	}
	else if (mode == INIT)
	{
		result = pthread_mutex_init(mutex, NULL);
		check_result(result, "pthread_mutex_init");
	}
	else if (mode == DESTROY)
	{
		result = pthread_mutex_destroy(mutex);
		check_result(result, "pthread_mutex_destroy");
	}
	else
		ft_exit("Wrong mode for mutex handle!");
}


// Wrapper sécurisé pour les opérations thread
void	safe_thread_handle(pthread_t *thread, void *(*foo)(void *),
						void *data, t_mode mode)
{
	int	result;

	result = 0;
	if (mode == CREATE)
	{
		result = pthread_create(thread, NULL, foo, data);
		check_result(result, "pthread_create");
	}
	else if (mode == JOIN)
	{
		result = pthread_join(*thread, NULL);
		check_result(result, "pthread_join");
	}
	else
		ft_exit("Wrong mode for thread_handle: use <CREATE> <JOIN>");
}
