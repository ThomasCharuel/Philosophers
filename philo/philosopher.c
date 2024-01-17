/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharuel <tcharuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 11:34:11 by tcharuel          #+#    #+#             */
/*   Updated: 2024/01/17 23:23:40 by tcharuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philosopher_tries_forks(t_philosopher *philosopher)
{
	t_timestamp	action_time;
	t_fork		*first_fork;
	t_fork		*second_fork;

	first_fork = &philosopher->simulation->forks[philosopher->id
		- philosopher->id % 2];
	second_fork = &philosopher->simulation->forks[philosopher->id
		- (philosopher->id + 1) % 2];
	lock(&first_fork->lock);
	lock(&second_fork->lock);
	lock(&philosopher->state_lock);
	if (philosopher->state == PHILOSOPHER_IS_DEAD || !first_fork->is_available
		|| !second_fork->is_available)
	{
		unlock(&philosopher->state_lock);
		unlock(&first_fork->lock);
		unlock(&second_fork->lock);
		return ;
	}
	action_time = get_current_time();
	first_fork->is_available = FALSE;
	unlock(&first_fork->lock);
	second_fork->is_available = FALSE;
	unlock(&second_fork->lock);
	log_action(action_time, PHILOSOPHER_TAKES_FORK, philosopher);
	set_philosopher_last_eating_time(philosopher, action_time);
	philosopher->state = PHILOSOPHER_IS_EATING;
	log_action(action_time, PHILOSOPHER_STARTS_EATING, philosopher);
	unlock(&philosopher->state_lock);
	if (philosopher->simulation->has_number_of_times_each_philosopher_must_eat)
		incr_philosopher_meal_count(philosopher);
}

void	philosopher_releases_forks(t_philosopher *philosopher)
{
	set_fork_availability(&philosopher->simulation->forks[philosopher->id - 1],
		TRUE);
	set_fork_availability(&philosopher->simulation->forks[philosopher->id
		% philosopher->simulation->number_of_philosophers], TRUE);
}

void	handle_philosopher_thinking(t_philosopher *philosopher)
{
	while (get_simulation_state(philosopher->simulation) != SIMULATION_ENDED
		&& get_philosopher_state(philosopher) == PHILOSOPHER_IS_THINKING)
	{
		philosopher_tries_forks(philosopher);
		usleep(10);
	}
}

void	handle_philosopher_eating(t_philosopher *philosopher)
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
			philosopher_releases_forks(philosopher);
			set_philosopher_state(philosopher, PHILOSOPHER_IS_SLEEPING);
			set_philosopher_last_sleeping_time(philosopher, current_time);
			log_action(current_time, PHILOSOPHER_STARTS_SLEEPING, philosopher);
			return ;
		}
		usleep(10);
	}
}

void	handle_philosopher_sleeping(t_philosopher *philosopher)
{
	t_timestamp	current_time;
	t_timestamp	last_sleeping_time;

	last_sleeping_time = get_philosopher_last_sleeping_time(philosopher);
	while (get_simulation_state(philosopher->simulation) != SIMULATION_ENDED
		&& get_philosopher_state(philosopher) == PHILOSOPHER_IS_SLEEPING)
	{
		current_time = get_current_time();
		if (current_time
			- last_sleeping_time > philosopher->simulation->time_to_sleep)
		{
			set_philosopher_state(philosopher, PHILOSOPHER_IS_THINKING);
			log_action(current_time, PHILOSOPHER_STARTS_THINKING, philosopher);
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
		handle_philosopher_thinking(philosopher);
		handle_philosopher_eating(philosopher);
		handle_philosopher_sleeping(philosopher);
		usleep(10);
	}
	return (NULL);
}
