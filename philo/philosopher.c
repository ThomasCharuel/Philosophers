/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharuel <tcharuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 11:34:11 by tcharuel          #+#    #+#             */
/*   Updated: 2024/01/16 18:32:18 by tcharuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philosopher_routine(void *data)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *)data;
	set_philosopher_state(philosopher, PHILOSOPHER_IS_THINKING);
	while (get_simulation_state(philosopher->simulation) == SIMULATION_INITIALIZING)
		usleep(10);
	while (get_simulation_state(philosopher->simulation) == SIMULATION_RUNNING)
	{
		usleep(10);
	}
	return (NULL);
}
