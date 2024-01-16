/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lock_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharuel <tcharuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 12:20:06 by tcharuel          #+#    #+#             */
/*   Updated: 2024/01/16 17:54:18 by tcharuel         ###   ########.fr       */
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

t_simulation_state get_simulation_state(t_simulation *simulation)
{
	t_simulation_state state;

	pthread_mutex_lock(&(simulation->state_lock.mutex));
	state = simulation->state;
	pthread_mutex_unlock(&(simulation->state_lock.mutex));
	return (state);
}

void set_simulation_state(t_simulation *simulation, t_simulation_state state)
{
	pthread_mutex_lock(&(simulation->state_lock.mutex));
	simulation->state = state;
	pthread_mutex_unlock(&(simulation->state_lock.mutex));
}

t_philosopher_state get_philosopher_state(t_philosopher *philosopher)
{
	t_philosopher_state state;

	pthread_mutex_lock(&(philosopher->state_lock.mutex));
	state = philosopher->state;
	pthread_mutex_unlock(&(philosopher->state_lock.mutex));
	return (state);
}

void set_philosopher_state(t_philosopher *philosopher, t_philosopher_state state)
{
	pthread_mutex_lock(&(philosopher->state_lock.mutex));
	philosopher->state = state;
	pthread_mutex_unlock(&(philosopher->state_lock.mutex));
}
