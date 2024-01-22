/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharuel <tcharuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 10:04:07 by tcharuel          #+#    #+#             */
/*   Updated: 2024/01/22 11:46:34 by tcharuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool	check_philosopher_is_alive(t_philosopher *philosopher)
{
	t_timestamp	current_time;

	current_time = get_current_time();
	if (current_time
		- philosopher->last_eating_time > philosopher->simulation->time_to_die)
	{
		log_action(current_time, PHILOSOPHER_DIES, philosopher);
		return (FALSE);
	}
	return (TRUE);
}

void	handle_philosopher_thinking(t_philosopher *philosopher)
{
	t_timestamp	current_time;

	if (philosopher->state == PHILOSOPHER_IS_THINKING
		&& philosopher->simulation->number_of_philosophers > 1)
	{
		sem_wait(philosopher->simulation->forks_pair_count);
		current_time = get_current_time();
		if (!check_philosopher_is_alive(philosopher))
			return ;
		philosopher->last_eating_time = current_time;
		philosopher->state = PHILOSOPHER_IS_EATING;
		log_action(current_time, PHILOSOPHER_STARTS_EATING, philosopher);
		if (philosopher->simulation->has_number_of_times_each_philosopher_must_eat)
		{
			philosopher->meal_count++;
			if (philosopher->meal_count == philosopher->simulation->number_of_times_each_philosopher_must_eat)
				sem_post(philosopher->simulation->philosopher_have_eaten_enough);
		}
	}
}

void	handle_philosopher_eating(t_philosopher *philosopher)
{
	(void)philosopher;
}

void	handle_philosopher_sleeping(t_philosopher *philosopher)
{
	(void)philosopher;
}

void	philosopher_routine(t_simulation *simulation,
		unsigned int philosopher_id)
{
	t_philosopher	philosopher;

	philosopher.simulation = simulation;
	philosopher.id = philosopher_id;
	philosopher.meal_count = 0;
	sem_post(simulation->philosopher_process_ready);
	sem_wait(simulation->ready);
	philosopher.start_time = get_current_time();
	philosopher.last_eating_time = philosopher.start_time;
	philosopher.state = PHILOSOPHER_IS_THINKING;
	log_action(philosopher.start_time, PHILOSOPHER_STARTS_THINKING,
		&philosopher);
	while (check_philosopher_is_alive(&philosopher))
	{
		handle_philosopher_thinking(&philosopher);
		handle_philosopher_eating(&philosopher);
		handle_philosopher_sleeping(&philosopher);
		usleep(10);
	}
	simulation_cleanup(simulation);
	exit(EXIT_SUCCESS);
}
