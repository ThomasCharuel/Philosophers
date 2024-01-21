/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharuel <tcharuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 10:04:07 by tcharuel          #+#    #+#             */
/*   Updated: 2024/01/21 09:57:52 by tcharuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool	philosopher_is_alive(t_philosopher *philosopher)
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

void	philosopher_routine(t_simulation *simulation,
		unsigned int philosopher_id)
{
	t_philosopher	philosopher;

	philosopher.simulation = simulation;
	philosopher.id = philosopher_id;
	sem_post(simulation->philosopher_process_ready);
	sem_wait(simulation->ready);
	philosopher.start_time = get_current_time();
	philosopher.last_eating_time = philosopher.start_time;
	while (philosopher_is_alive(&philosopher))
	{
		// Do philosopher actions
		usleep(10);
	}
	exit(EXIT_SUCCESS);
}
