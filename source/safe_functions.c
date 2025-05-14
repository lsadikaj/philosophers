/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadikaj <lsadikaj@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 11:58:55 by lsadikaj          #+#    #+#             */
/*   Updated: 2025/05/14 15:31:52 by lsadikaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*safe_malloc(size_t	bytes)
{
	void	*ret;
	
	ret = malloc(bytes);
	if (!ret)
		clean_exit("Error with the malloc!\n");
	return (ret);
}

static void	handle_mutex_error(int status, t_opcode opcode)
{
	if (0 == status)
		return ;
	if (EINVAL == status && (LOCK == opcode || UNLOCK == opcode))
		clean_exit("The value specified by mutex is invalid.\n");
	else if (EINVAL == status && INIT == opcode)
		clean_exit("The value specified by attr is invalid.\n");
	else if (EINVAL == status && DESTROY == opcode)
		clean_exit("The value specified by mutex"
					" is invalid for destruction.\n");
	else if (EDEADLK == status)
		clean_exit("A deadlock would occur if the thread"
					" blocked waiting for mutex.\n");
	else if (EPERM == status)
		clean_exit("The current thread does not hold a lock on mutex.\n");
	else if (ENOMEM == status)
		clean_exit("The process cannot allocate enough memory"
					" to create another mutex.\n");
	else if (EBUSY == status && DESTROY == opcode)
		clean_exit("Mutex is locked or referenced by another"
					" thread and cannot be destroyed.\n");
	else if (EBUSY == status)
		clean_exit("Mutex is locked.\n");
}

void	safe_mutex_handle(t_mtx *mutex, t_opcode opcode)
{
	int status;
	
	if (LOCK == opcode)
		handle_mutex_error(pthread_mutex_lock(mutex), opcode);
	else if (UNLOCK == opcode)
		handle_mutex_error(pthread_mutex_unlock(mutex), opcode);
	else if (INIT == opcode)
		handle_mutex_error(pthread_mutex_init(mutex, NULL), opcode);
	else if (DESTROY == opcode)
		handle_mutex_error(pthread_mutex_destroy(mutex), opcode);
	else
		clean_exit("Wrong opcode for mutex handle!\n");
}

static void	handle_thread_error(int status, t_opcode opcode)
{
	if (0 == status)
		return ;
	if (EAGAIN == status)
		clean_exit("No ressources to create another thread.\n");
	else if (EPERM == status)
		clean_exit("The caller does not have appropriate permissions.\n");
	else if (EINVAL == status)
		clean_exit("The value specified by attr is invalid.\n");
	else if (ESRCH == status)
		clean_exit("No thread could be found to that specified by the"
					" given thread ID, thread.\n");
	else if (EDEADLK == status)
		clean_exit("A deadlock was detected or the value of thread"
					" specifies the calling thread.\n");
}

void	safe_thread_handle(pthread_t *thread, void *(*foo)(void *),
							void *data, t_opcode opcode)
{
	if (CREATE == opcode)
		handle_thread_error(pthread_create(thread, NULL, foo, data), opcode);
	else if (JOIN == opcode)
		handle_thread_error(pthread_join(*thread, NULL), opcode);
	else if (DETACH == opcode)
		handle_thread_error(pthread_detach(*thread), opcode);
	else
		clean_exit("Wrong opcode for thread_handle:"
					"use <CREATE> <JOIN> <DETACH>\n");
}
