/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharuel <tcharuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 11:34:11 by tcharuel          #+#    #+#             */
/*   Updated: 2024/01/22 18:08:29 by tcharuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_fork	*get_left_fork(t_philosopher *philosopher)
{
	t_fork	*fork;

	fork = &(philosopher->simulation->forks[philosopher->id - 1]);
	return (fork);
}

t_fork	*get_right_fork(t_philosopher *philosopher)
{
	t_fork	*fork;

	fork = &(philosopher->simulation->forks[philosopher->id
			% philosopher->simulation->number_of_philosophers]);
	return (fork);
}

void	philosopher_tries_forks(t_philosopher *philosopher)
{
	t_timestamp	action_time;
	t_fork		*fork;

	action_time = get_current_time();
	lock(&philosopher->state_lock);
	if ((philosopher->state == PHILOSOPHER_IS_THINKING && philosopher->id % 2)
		|| (philosopher->state == PHILOSOPHER_HAS_ONE_FORK && philosopher->id
			% 2 == 0))
		fork = get_right_fork(philosopher);
	else if ((philosopher->state == PHILOSOPHER_HAS_ONE_FORK && philosopher->id
			% 2) || (philosopher->state == PHILOSOPHER_IS_THINKING
			&& philosopher->id % 2 == 0))
		fork = get_left_fork(philosopher);
	else
	{
		unlock(&philosopher->state_lock);
		return ;
	}
	lock(&fork->lock);
	if (!fork->is_available)
	{
		unlock(&philosopher->state_lock);
		unlock(&fork->lock);
		return ;
	}
	fork->is_available = FALSE;
	unlock(&fork->lock);
	log_action(action_time, PHILOSOPHER_TAKES_FORK, philosopher);
	if (philosopher->state == PHILOSOPHER_IS_THINKING)
		philosopher->state = PHILOSOPHER_HAS_ONE_FORK;
	else
	{
		set_philosopher_last_eating_time(philosopher, action_time);
		philosopher->state = PHILOSOPHER_IS_EATING;
		log_action(action_time, PHILOSOPHER_STARTS_EATING, philosopher);
		if (philosopher->simulation->has_number_of_times_each_philosopher_must_eat)
			incr_philosopher_meal_count(philosopher);
	}
	unlock(&philosopher->state_lock);
}

void	philosopher_releases_forks(t_philosopher *philosopher)
{
	unlock(get_left_fork(philosopher));
	unlock(get_right_fork(philosopher));
}

void	handle_philosopher_thinking(t_philosopher *philosopher)
{
	while (get_simulation_state(philosopher->simulation) != SIMULATION_ENDED
		&& (get_philosopher_state(philosopher) == PHILOSOPHER_IS_THINKING
			|| get_philosopher_state(philosopher) == PHILOSOPHER_HAS_ONE_FORK))
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
	while (get_simulation_state(philosopher->simulation) != SIMULATION_ENDED
		&& get_philosopher_state(philosopher) == PHILOSOPHER_IS_EATING)
	{
		current_time = get_current_time();
		if (current_time
			- last_eating_time >= philosopher->simulation->time_to_eat)
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
			- last_sleeping_time >= philosopher->simulation->time_to_sleep)
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
