/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharuel <tcharuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 10:04:07 by tcharuel          #+#    #+#             */
/*   Updated: 2024/01/23 13:05:43 by tcharuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*check_philosopher_alive_routine(void *data)
{
	t_philosopher	*philosopher;
	t_simulation	*simulation;
	t_timestamp		current_time;
	t_timestamp		last_eating;

	philosopher = (t_philosopher *)data;
	simulation = philosopher->simulation;
	while (usleep(1000) == 0)
	{
		current_time = get_current_time();
		sem_wait(simulation->last_eating_check);
		last_eating = philosopher->last_eating;
		sem_post(simulation->last_eating_check);
		if (current_time - last_eating > simulation->time_to_die)
		{
			log_action(current_time, PHILOSOPHER_DIES, philosopher);
			sem_post(simulation->has_ended);
			return (NULL);
		}
	}
	return (NULL);
}

void	handle_philosopher_thinking(t_philosopher *philosopher)
{
	t_timestamp	current_time;

	sem_wait(philosopher->simulation->forks_pair_count);
	current_time = get_current_time();
	sem_wait(philosopher->simulation->last_eating_check);
	philosopher->last_eating = current_time;
	sem_post(philosopher->simulation->last_eating_check);
	philosopher->state = PHILOSOPHER_IS_EATING;
	log_action(current_time, PHILOSOPHER_STARTS_EATING, philosopher);
	if (philosopher->simulation->min_meals > 0)
	{
		philosopher->meal_count++;
		if (philosopher->meal_count == philosopher->simulation->min_meals)
			sem_post(philosopher->simulation->philosopher_have_eaten_enough);
	}
}

void	handle_philosopher_eating(t_philosopher *philosopher)
{
	t_timestamp	current_time;
	t_timestamp	last_eating;

	current_time = get_current_time();
	sem_wait(philosopher->simulation->last_eating_check);
	last_eating = philosopher->last_eating;
	sem_post(philosopher->simulation->last_eating_check);
	if (current_time - last_eating >= philosopher->simulation->time_to_eat)
	{
		log_action(current_time, PHILOSOPHER_STARTS_SLEEPING, philosopher);
		sem_post(philosopher->simulation->forks_pair_count);
		philosopher->last_sleeping = current_time;
		philosopher->state = PHILOSOPHER_IS_SLEEPING;
	}
}

void	handle_philosopher_sleeping(t_philosopher *philosopher)
{
	t_timestamp	elapsed_sleeping;
	t_timestamp	current_time;

	current_time = get_current_time();
	elapsed_sleeping = current_time - philosopher->last_sleeping;
	if (elapsed_sleeping >= philosopher->simulation->time_to_sleep)
	{
		log_action(current_time, PHILOSOPHER_STARTS_THINKING, philosopher);
		philosopher->state = PHILOSOPHER_IS_THINKING;
	}
}

void	philosopher_routine(t_simulation *simulation,
		unsigned int philosopher_id)
{
	t_philosopher	philosopher;
	pthread_t		monitoring_thread;

	philosopher.simulation = simulation;
	philosopher.id = philosopher_id;
	philosopher.meal_count = 0;
	sem_post(simulation->philosopher_process_ready);
	sem_wait(simulation->ready);
	philosopher.start_time = get_current_time();
	philosopher.last_eating = philosopher.start_time;
	philosopher.state = PHILOSOPHER_IS_THINKING;
	log_action(philosopher.start_time, PHILOSOPHER_STARTS_THINKING,
		&philosopher);
	pthread_create(&monitoring_thread, NULL, &check_philosopher_alive_routine,
		&philosopher);
	while (usleep(10) == 0)
	{
		if (philosopher.state == PHILOSOPHER_IS_THINKING
			&& simulation->philosophers_count > 1)
			handle_philosopher_thinking(&philosopher);
		if (philosopher.state == PHILOSOPHER_IS_EATING)
			handle_philosopher_eating(&philosopher);
		if (philosopher.state == PHILOSOPHER_IS_SLEEPING)
			handle_philosopher_sleeping(&philosopher);
	}
}
