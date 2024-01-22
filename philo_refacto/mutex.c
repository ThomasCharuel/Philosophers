/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharuel <tcharuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 18:13:56 by tcharuel          #+#    #+#             */
/*   Updated: 2024/01/22 18:25:23 by tcharuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_lock(t_lock *lock)
{
	lock->is_initialized = false;
	if (pthread_mutex_init(&(lock->mutex), NULL) != 0)
		return (ERROR);
	lock->is_initialized = true;
	return (SUCCESS);
}

void	destroy_lock(t_lock *lock)
{
	if (lock->is_initialized)
	{
		pthread_mutex_destroy(&lock->mutex);
		lock->is_initialized = false;
	}
}

void	lock(t_lock *lock)
{
	pthread_mutex_lock(&(lock->mutex));
}

void	unlock(t_lock *lock)
{
	pthread_mutex_unlock(&(lock->mutex));
}
