/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lock_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharuel <tcharuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 12:20:06 by tcharuel          #+#    #+#             */
/*   Updated: 2024/01/17 16:32:42 by tcharuel         ###   ########.fr       */
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

void	lock(t_lock *lock)
{
	pthread_mutex_lock(&(lock->mutex));
}

void	unlock(t_lock *lock)
{
	pthread_mutex_unlock(&(lock->mutex));
}

t_simulation_state	get_simulation_state(t_simulation *simulation)
{
	t_simulation_state	state;

	lock(&simulation->state_lock);
	state = simulation->state;
	unlock(&simulation->state_lock);
	return (state);
}

void	set_simulation_state(t_simulation *simulation, t_simulation_state state)
{
	lock(&simulation->state_lock);
	simulation->state = state;
	unlock(&simulation->state_lock);
}

t_philosopher_state	get_philosopher_state(t_philosopher *philosopher)
{
	t_philosopher_state	state;

	lock(&philosopher->state_lock);
	state = philosopher->state;
	unlock(&philosopher->state_lock);
	return (state);
}

void	set_philosopher_state(t_philosopher *philosopher,
		t_philosopher_state state)
{
	lock(&philosopher->state_lock);
	philosopher->state = state;
	unlock(&philosopher->state_lock);
}

t_timestamp	get_philosopher_last_eating_time(t_philosopher *philosopher)
{
	t_timestamp	last_eating_time;

	lock(&philosopher->last_eating_time_lock);
	last_eating_time = philosopher->last_eating_time;
	unlock(&philosopher->last_eating_time_lock);
	return (last_eating_time);
}

void	set_philosopher_last_eating_time(t_philosopher *philosopher,
		t_timestamp last_eating_time)
{
	lock(&philosopher->last_eating_time_lock);
	philosopher->last_eating_time = last_eating_time;
	unlock(&philosopher->last_eating_time_lock);
}
