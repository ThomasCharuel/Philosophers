/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharuel <tcharuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 18:58:27 by tcharuel          #+#    #+#             */
/*   Updated: 2024/01/22 19:39:56 by tcharuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_simulation_state	get_simulation_state(t_simulation *simulation)
{
	t_simulation_state	state;

	lock(&simulation->state_lock);
	state = simulation->state;
	unlock(&simulation->state_lock);
	return (state);
}

t_philosopher_state	get_philosopher_state(t_philosopher *philosopher)
{
	t_philosopher_state	state;

	lock(&philosopher->state_lock);
	state = philosopher->state;
	unlock(&philosopher->state_lock);
	return (state);
}

t_timestamp	get_philosopher_last_eating(t_philosopher *philosopher)
{
	t_timestamp	last_eating;

	lock(&philosopher->last_eating_lock);
	last_eating = philosopher->last_eating;
	unlock(&philosopher->last_eating_lock);
	return (last_eating);
}

unsigned int	get_philosopher_meal_count(t_philosopher *philosopher)
{
	unsigned int	meal_count;

	lock(&philosopher->meal_count_lock);
	meal_count = philosopher->meal_count;
	unlock(&philosopher->meal_count_lock);
	return (meal_count);
}
