/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharuel <tcharuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 18:53:03 by tcharuel          #+#    #+#             */
/*   Updated: 2024/01/22 20:29:07 by tcharuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	handle_philosopher_thinking(t_philosopher *philosopher)
{
	t_lock		*fork;
	t_timestamp	current_time;

	if ((get_philosopher_state(philosopher) == PHILOSOPHER_IS_THINKING
			&& philosopher->id % 2)
		|| (philosopher->state == PHILOSOPHER_HAS_ONE_FORK && philosopher->id
			% 2 == 0))
	{
		fork = get_right_fork(philosopher);
		lock(fork);
		philosopher->forks[1] = fork;
	}
	else if ((philosopher->state == PHILOSOPHER_HAS_ONE_FORK && philosopher->id
			% 2) || (philosopher->state == PHILOSOPHER_IS_THINKING
			&& philosopher->id % 2 == 0))
	{
		fork = get_left_fork(philosopher);
		lock(fork);
		philosopher->forks[0] = fork;
	}
	else
		return ;
	current_time = get_current_time();
	// Here
	lock(&philosopher->state_lock);
	log_action(current_time, PHILOSOPHER_TAKES_FORK, philosopher);
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
			philosopher_releases_forks(philosopher);
			log_action(current_time, PHILOSOPHER_STARTS_SLEEPING, philosopher);
			philosopher->last_sleeping = current_time;
			set_philosopher_state(philosopher, PHILOSOPHER_IS_SLEEPING);
			return ;
		}
	}
}

void	handle_philosopher_sleeping(t_philosopher *philosopher)
{
	t_timestamp	current_time;

	while (get_philosopher_state(philosopher) == PHILOSOPHER_IS_SLEEPING
		&& usleep(10) == 0)
	{
		current_time = get_current_time();
		if (current_time
			- philosopher->last_sleeping >= philosopher->simulation->time_to_sleep)
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
	return (NULL);
}
