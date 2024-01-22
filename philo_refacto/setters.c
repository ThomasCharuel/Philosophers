/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharuel <tcharuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 18:58:27 by tcharuel          #+#    #+#             */
/*   Updated: 2024/01/22 19:39:31 by tcharuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_simulation_state(t_simulation *simulation, t_simulation_state state)
{
	lock(&simulation->state_lock);
	simulation->state = state;
	unlock(&simulation->state_lock);
}

void	set_philosopher_state(t_philosopher *philosopher,
		t_philosopher_state state)
{
	lock(&philosopher->state_lock);
	philosopher->state = state;
	unlock(&philosopher->state_lock);
}

void	set_philosopher_last_eating(t_philosopher *philosopher,
		t_timestamp last_eating)
{
	lock(&philosopher->last_eating_lock);
	philosopher->last_eating = last_eating;
	unlock(&philosopher->last_eating_lock);
}

void	incr_philosopher_meal_count(t_philosopher *philosopher)
{
	lock(&philosopher->meal_count_lock);
	philosopher->meal_count++;
	unlock(&philosopher->meal_count_lock);
}
