/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharuel <tcharuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 11:34:11 by tcharuel          #+#    #+#             */
/*   Updated: 2024/01/11 14:22:46 by tcharuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philosopher_routine(void *data)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *)data;
	printf_locked("%u philosopher\n", philosopher->id);
	// if (philosopher->simulation_state->is_running)
	// {
	// if (has_starved(last_eating_timestamp, time_to_die))
	// {
	printf("%u died\n", philosopher->id);
	// 	return (NULL);
	// }
	// if (philosopher->state == IS_THINKING)
	// {
	// }
	// 	printf("%u philosopher\n", philosopher->id);
	// }
	return (NULL);
}
