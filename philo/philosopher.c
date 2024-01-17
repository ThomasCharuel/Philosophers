/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharuel <tcharuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 11:34:11 by tcharuel          #+#    #+#             */
/*   Updated: 2024/01/17 16:43:44 by tcharuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philosopher_takes_fork(t_philosopher *philosopher,
		t_fork_side fork_side)
{
	t_timestamp	action_time;

	if (fork_side == LEFT_FORK)
		lock(&philosopher->simulation->forks[philosopher->id - 1].lock);
	else if (fork_side == RIGHT_FORK)
		lock(&philosopher->simulation->forks[philosopher->id
			% philosopher->simulation->number_of_philosophers].lock);
	action_time = get_current_time();
	lock(&philosopher->state_lock);
	if (philosopher->state != PHILOSOPHER_IS_DEAD)
	{
		log_action(action_time, PHILOSOPHER_TAKES_FORK, philosopher);
		if (philosopher->state == PHILOSOPHER_HAS_RIGHT_FORK
			|| philosopher->state == PHILOSOPHER_HAS_LEFT_FORK)
		{
			set_philosopher_last_eating_time(philosopher, action_time);
			philosopher->state = PHILOSOPHER_IS_EATING;
			log_action(action_time, PHILOSOPHER_STARTS_EATING, philosopher);
		}
		else if (fork_side == LEFT_FORK)
			philosopher->state = PHILOSOPHER_HAS_LEFT_FORK;
		else if (fork_side == RIGHT_FORK)
			philosopher->state = PHILOSOPHER_HAS_RIGHT_FORK;
	}
	unlock(&philosopher->state_lock);
}

void	philosopher_releases_forks(t_philosopher *philosopher)
{
	unlock(&philosopher->simulation->forks[philosopher->id - 1].lock);
	unlock(&philosopher->simulation->forks[philosopher->id
		% philosopher->simulation->number_of_philosophers].lock);
}

void	philosopher_is_eating(t_philosopher *philosopher)
{
	t_timestamp	current_time;
	t_timestamp	last_eating_time;

	last_eating_time = get_philosopher_last_eating_time(philosopher);
	while (get_philosopher_state(philosopher) == PHILOSOPHER_IS_EATING
		&& get_simulation_state(philosopher->simulation) != SIMULATION_ENDED)
	{
		current_time = get_current_time();
		if (current_time
			- last_eating_time > philosopher->simulation->time_to_eat)
		{
			set_philosopher_state(philosopher, PHILOSOPHER_IS_SLEEPING);
			log_action(current_time, PHILOSOPHER_STARTS_SLEEPING, philosopher);
			return ;
		}
		usleep(10);
	}
}

void	*philosopher_routine(void *data)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *)data;
	set_philosopher_state(philosopher, PHILOSOPHER_IS_THINKING);
	while (get_simulation_state(philosopher->simulation) == SIMULATION_INITIALIZING)
		usleep(10);
	while (get_simulation_state(philosopher->simulation) == SIMULATION_RUNNING)
	{
		if (get_philosopher_state(philosopher) == PHILOSOPHER_IS_THINKING)
		{
			philosopher_takes_fork(philosopher, philosopher->id % 2);
			philosopher_takes_fork(philosopher, (philosopher->id + 1) % 2);
			philosopher_is_eating(philosopher);
			philosopher_releases_forks(philosopher);
		}
		usleep(10);
	}
	return (NULL);
}
