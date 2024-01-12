/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharuel <tcharuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 11:34:11 by tcharuel          #+#    #+#             */
/*   Updated: 2024/01/12 15:28:08 by tcharuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philosopher_routine(void *data)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *)data;
	pthread_mutex_lock(&(philosopher->simulation_state->printf_lock.mutex));
	printf("%d philosopher\n", philosopher->id);
	pthread_mutex_unlock(&(philosopher->simulation_state->printf_lock.mutex));
	// if (philosopher->simulation_state->is_running)
	// {
	// if (has_starved(last_eating_timestamp, time_to_die))
	// {
	// 	return (NULL);
	// }
	// if (philosopher->state == IS_THINKING)
	// {
	// }
	// 	printf("%u philosopher\n", philosopher->id);
	// }
	return (NULL);
}
