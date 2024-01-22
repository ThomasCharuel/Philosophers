/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharuel <tcharuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 18:53:03 by tcharuel          #+#    #+#             */
/*   Updated: 2024/01/22 19:58:37 by tcharuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	handle_philosopher_thinking(t_philosopher *philosopher)
{
	(void)philosopher;
}

void	handle_philosopher_eating(t_philosopher *philosopher)
{
	(void)philosopher;
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
			set_philosopher_state(philosopher, PHILOSOPHER_IS_THINKING);
			log_action(current_time, PHILOSOPHER_STARTS_THINKING, philosopher);
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
