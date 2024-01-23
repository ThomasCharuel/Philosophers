/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharuel <tcharuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 18:53:03 by tcharuel          #+#    #+#             */
/*   Updated: 2024/01/23 12:27:04 by tcharuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	handle_philosopher_thinking(t_philosopher *philosopher)
{
	t_timestamp	current_time;

	lock(&philosopher->state_lock);
	if (get_target_fork(philosopher) == ERROR)
	{
		unlock(&philosopher->state_lock);
		return ;
	}
	current_time = get_current_time();
	if (philosopher->state == PHILOSOPHER_IS_THINKING)
	{
		log_action(current_time, PHILOSOPHER_TAKES_FORK, philosopher);
		philosopher->state = PHILOSOPHER_HAS_ONE_FORK;
	}
	else if (philosopher->state == PHILOSOPHER_HAS_ONE_FORK)
	{
		log_action(current_time, PHILOSOPHER_TAKES_FORK, philosopher);
		log_action(current_time, PHILOSOPHER_STARTS_EATING, philosopher);
		philosopher->state = PHILOSOPHER_IS_EATING;
		set_philosopher_last_eating(philosopher, current_time);
		if (philosopher->simulation->min_meals > 0)
			incr_philosopher_meal_count(philosopher);
	}
	unlock(&philosopher->state_lock);
}

void	handle_philosopher_eating(t_philosopher *philosopher)
{
	t_timestamp	current_time;
	t_timestamp	last_eating;

	last_eating = get_philosopher_last_eating(philosopher);
	while (get_philosopher_state(philosopher) == PHILOSOPHER_IS_EATING
		&& usleep(10) == 0)
	{
		current_time = get_current_time();
		if (current_time - last_eating >= philosopher->simulation->time_to_eat)
		{
			log_action(current_time, PHILOSOPHER_STARTS_SLEEPING, philosopher);
			philosopher->last_sleeping = current_time;
			set_philosopher_state(philosopher, PHILOSOPHER_IS_SLEEPING);
			philosopher_releases_forks(philosopher);
			return ;
		}
	}
}

void	handle_philosopher_sleeping(t_philosopher *philosopher)
{
	t_timestamp	current_time;
	t_timestamp	last_sleeping;

	last_sleeping = philosopher->last_sleeping;
	while (get_philosopher_state(philosopher) == PHILOSOPHER_IS_SLEEPING
		&& usleep(10) == 0)
	{
		current_time = get_current_time();
		if (current_time
			- last_sleeping >= philosopher->simulation->time_to_sleep)
		{
			log_action(current_time, PHILOSOPHER_STARTS_THINKING, philosopher);
			set_philosopher_state(philosopher, PHILOSOPHER_IS_THINKING);
			return ;
		}
	}
}

void	*philosopher_routine(void *data)
{
	t_philosopher	*philosopher;
	t_simulation	*simulation;

	philosopher = (t_philosopher *)data;
	simulation = philosopher->simulation;
	set_philosopher_state(philosopher, PHILOSOPHER_IS_THINKING);
	while (get_simulation_state(simulation) == SIMULATION_INITIALIZING)
		usleep(10);
	while (get_simulation_state(simulation) == SIMULATION_RUNNING
		&& usleep(10) == 0)
	{
		handle_philosopher_thinking(philosopher);
		handle_philosopher_eating(philosopher);
		handle_philosopher_sleeping(philosopher);
	}
	philosopher_releases_forks(philosopher);
	return (NULL);
}
