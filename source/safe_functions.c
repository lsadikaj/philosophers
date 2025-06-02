/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadikaj <lsadikaj@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 11:58:55 by lsadikaj          #+#    #+#             */
/*   Updated: 2025/06/02 18:30:01 by lsadikaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/*
** Alloue de la mémoire de manière sécurisée
** Vérifie si l'allocation a réussi et termine le programme en cas d'échec
*/
void	*ft_malloc(size_t bytes)
{
	void	*ret;
	
	ret = malloc(bytes);
	if (!ret)
		ft_exit("Error with malloc!");
	return (ret);
}

/*
** Gère les erreurs des opérations de mutex
** Analyse le statut retourné et le type d'opération, et termine le programme
** avec un message d'erreur approprié en cas de problème
*/
static void	handle_mutex_error(int status, t_mode mode)
{
	if (status == 0)
		return ;
	if (status == EINVAL&& (mode == LOCK || mode == UNLOCK))
		ft_exit("The value specified by mutex is invalid");
	else if (status == EINVAL && mode == INIT)
		ft_exit("The value specified by attr is invalid");
	else if (status == EINVAL && mode == DESTROY)
		ft_exit("The value specified by mutex is invalid for destruction");
	else if (status == EDEADLK)
		ft_exit("A deadlock would occur if the thread blocked waiting for mutex");
	else if (status == EPERM)
		ft_exit("The current thread does not hold a lock on mutex");
	else if (status == ENOMEM)
		ft_exit("The process cannot allocate enough memory to create another mutex");
	else if (status == EBUSY && mode == DESTROY)
		ft_exit("Mutex is locked or referenced by another thread and cannot be destroyed");
	else if (status == EBUSY)
		ft_exit("Mutex is locked");
}

/*
** Gère les opérations sur les mutex de manière sécurisée
** Effectue les opérations demandées (lock, unlock, init, destroy) et vérifie
** qu'elles se sont déroulées correctement
*/
void	safe_mutex_handle(t_mtx *mutex, t_mode mode)
{
	int	status;
	
	if (mode == LOCK)
	{
		status = pthread_mutex_lock(mutex);
		handle_mutex_error(status, mode);
	}
	else if (mode == UNLOCK)
	{
		status = pthread_mutex_unlock(mutex);
		handle_mutex_error(status, mode);
	}
	else if (mode == INIT)
	{
		status = pthread_mutex_init(mutex, NULL);
		handle_mutex_error(status, mode);
	}
	else if (mode == DESTROY)
	{
		status = pthread_mutex_destroy(mutex);
		handle_mutex_error(status, mode);
	}
	else
		ft_exit("Wrong opcode for mutex handle!");
}

/*
** Gère les erreurs des opérations de thread
** Analyse le statut retourné et le type d'opération, et termine le programme
** avec un message d'erreur approprié en cas de problème
*/
static void	handle_thread_error(int status, t_mode mode)
{
	if (status == 0)
		return ;
	if (status == EAGAIN)
	{
		if (mode == CREATE)
			ft_exit("Insufficient resources to create another thread");
		else
			ft_exit("No resources to perform the operation");
	}
	else if (status == EPERM)
	{
		if (mode == CREATE)
			ft_exit("No permission to create a thread");
		else if (mode == DETACH)
			ft_exit("No permission to detach the thread");
		else if (mode == JOIN)
			ft_exit("No permission to join with the thread");
		else
			ft_exit("The caller does not have appropriate permissions");
	}
	else if (status == EINVAL)
	{
		if (mode == CREATE)
			ft_exit("Invalid attributes for thread creation");
		else if (mode == JOIN)
			ft_exit("The thread is not joinable or another thread is already waiting");
		else if (mode == DETACH)
			ft_exit("The thread is not detachable");
		else
			ft_exit("The value specified by attr is invalid");
	}
	else if (status == ESRCH)
		ft_exit("No thread found with the specified thread ID");
	else if (status == EDEADLK)
		ft_exit("A deadlock was detected or the thread is attempting to join with itself");
}

/*
** Gère les opérations sur les threads de manière sécurisée
** Effectue les opérations demandées (create, join, detach) et vérifie
** qu'elles se sont déroulées correctement
*/
void	safe_thread_handle(pthread_t *thread, void *(*foo)(void *),
							void *data, t_mode mode)
{
	int	status;
	
	if (mode == CREATE)
	{
		status = pthread_create(thread, NULL, foo, data);
		handle_thread_error(status, mode);
	}
	else if (mode == JOIN)
	{
		status = pthread_join(*thread, NULL);
		handle_thread_error(status, mode);
	}
	else if (mode == DETACH)
	{
		status = pthread_detach(*thread);
		handle_thread_error(status, mode);
	}
	else
		ft_exit("Wrong opcode for thread_handle: use <CREATE> <JOIN> <DETACH>");
}
