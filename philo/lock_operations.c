/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lock_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharuel <tcharuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 12:20:06 by tcharuel          #+#    #+#             */
/*   Updated: 2024/01/11 12:25:23 by tcharuel         ###   ########.fr       */
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

void	locked_printf(t_lock lock)
{
	pthread_mutex_lock(&lock.mutex);
	pthread_mutex_unlock(&lock.mutex);
}
