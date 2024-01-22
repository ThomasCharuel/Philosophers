/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharuel <tcharuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 15:55:57 by tcharuel          #+#    #+#             */
/*   Updated: 2024/01/22 17:27:22 by tcharuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_simulation_starts(t_simulation *simulation)
{
	size_t	i;

	i = 0;
	while (i < simulation->number_of_philosophers)
	{
		while (get_philosopher_state(&simulation->philosophers[i]) != PHILOSOPHER_IS_THINKING)
			usleep(10);
		i++;
	}
	simulation->start_time = get_current_time();
	i = 0;
	while (i < simulation->number_of_philosophers)
	{
		set_philosopher_last_eating_time(&simulation->philosophers[i],
			simulation->start_time);
		log_action(simulation->start_time, PHILOSOPHER_STARTS_THINKING,
			&simulation->philosophers[i]);
		i++;
	}
	set_simulation_state(simulation, SIMULATION_RUNNING);
}

void	handle_end_simulation(t_simulation *simulation)
{
	size_t	i;

	set_simulation_state(simulation, SIMULATION_ENDED);
	i = 0;
	while (i < simulation->number_of_philosophers)
		pthread_join(simulation->philosophers[i++].tid, NULL);
}

t_bool	has_enough_meals_eaten(t_simulation *simulation)
{
	size_t	i;

	if (!simulation->has_number_of_times_each_philosopher_must_eat)
		return (FALSE);
	i = 0;
	while (i < simulation->number_of_philosophers)
	{
		if (get_philosopher_meal_count(&simulation->philosophers[i]) >= simulation->number_of_times_each_philosopher_must_eat)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

void	wait_simulation_ends(t_simulation *simulation)
{
	size_t		i;
	t_timestamp	current_time;

	while (!has_enough_meals_eaten(simulation) && usleep(10) == 0)
	{
		i = 0;
		current_time = get_current_time();
		while (i < simulation->number_of_philosophers)
		{
			if (current_time
				- get_philosopher_last_eating_time(&simulation->philosophers[i]) > simulation->time_to_die)
			{
				set_philosopher_state(&simulation->philosophers[i],
					PHILOSOPHER_IS_DEAD);
				log_action(current_time, PHILOSOPHER_DIES,
					&simulation->philosophers[i]);
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
		handle_end_simulation(&simulation);
		simulation_cleanup(&simulation);
	}
	return (0);
}
