/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharuel <tcharuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 18:53:03 by tcharuel          #+#    #+#             */
/*   Updated: 2024/01/22 19:48:17 by tcharuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philosopher_routine(void *data)
{
	t_philosopher	*philosopher;
	t_simulation	*simulation;

	philosopher = (t_philosopher *)data;
	simulation = philosopher->simulation;
	set_philosopher_state(philosopher, PHILOSOPHER_IS_THINKING);
	while (get_simulation_state(simulation) == SIMULATION_INITIALIZING)
		usleep(10);
	while (get_simulation_state(simulation) == SIMULATION_RUNNING)
	{
		// handle_philosopher_thinking(philosopher);
		// handle_philosopher_eating(philosopher);
		// handle_philosopher_sleeping(philosopher);
		usleep(10);
	}
	return (NULL);
}
