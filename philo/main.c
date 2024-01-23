/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharuel <tcharuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 18:09:43 by tcharuel          #+#    #+#             */
/*   Updated: 2024/01/23 13:37:39 by tcharuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_simulation_starts(t_simulation *simulation)
{
	size_t			i;
	t_philosopher	*philosopher;

	i = 0;
	while (i < simulation->philosophers_count)
	{
		philosopher = &simulation->philosophers[i];
		while (get_philosopher_state(philosopher) != PHILOSOPHER_IS_THINKING)
			usleep(10);
		i++;
	}
	simulation->start_time = get_current_time();
	i = 0;
	while (i < simulation->philosophers_count)
	{
		set_philosopher_last_eating(&simulation->philosophers[i],
			simulation->start_time);
		log_action(simulation->start_time, PHILOSOPHER_STARTS_THINKING,
			&simulation->philosophers[i]);
		i++;
	}
	set_simulation_state(simulation, SIMULATION_RUNNING);
}

t_bool	has_enough_meals_eaten(t_simulation *simulation)
{
	size_t			i;
	t_philosopher	*philosopher;

	if (!simulation->min_meals)
		return (FALSE);
	i = 0;
	while (i < simulation->philosophers_count)
	{
		philosopher = &simulation->philosophers[i];
		if (get_philosopher_meal_count(philosopher) < simulation->min_meals)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

void	wait_simulation_ends(t_simulation *simulation)
{
	size_t			i;
	t_timestamp		current_time;
	t_timestamp		last_eating;
	t_philosopher	*philosopher;

	while (!has_enough_meals_eaten(simulation))
	{
		i = 0;
		while (i < simulation->philosophers_count && usleep(10) == 0)
		{
			philosopher = &simulation->philosophers[i];
			last_eating = get_philosopher_last_eating(philosopher);
			current_time = get_current_time();
			if (current_time - last_eating > simulation->time_to_die)
			{
				set_philosopher_state(philosopher, PHILOSOPHER_IS_DEAD);
				log_action(current_time, PHILOSOPHER_DIES, philosopher);
				return ;
			}
			i++;
		}
	}
}

int	main(int argc, char **argv)
{
	t_simulation	simulation;

	if (argc == 5 || argc == 6)
	{
		if (simulation_init(argc, argv, &simulation) == ERROR)
		{
			simulation_cleanup(&simulation);
			return (0);
		}
		wait_simulation_starts(&simulation);
		wait_simulation_ends(&simulation);
		simulation_cleanup(&simulation);
	}
	return (0);
}
