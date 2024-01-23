/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharuel <tcharuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 15:55:57 by tcharuel          #+#    #+#             */
/*   Updated: 2024/01/23 12:29:19 by tcharuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philosophers_have_eaten_enough_monitoring_routine(void *data)
{
	unsigned int	i;
	t_simulation	*simulation;

	simulation = (t_simulation *)data;
	i = 0;
	while (i < simulation->philosophers_count)
	{
		sem_wait(simulation->philosopher_have_eaten_enough);
		i++;
	}
	sem_wait(simulation->is_running);
	sem_post(simulation->has_ended);
	return (NULL);
}

void	wait_simulation_starts(t_simulation *simulation)
{
	unsigned int	i;

	if (simulation->min_meals > 0)
	{
		pthread_create(&(simulation->enough_meal_monitoring_tid), NULL,
			philosophers_have_eaten_enough_monitoring_routine, simulation);
	}
	i = 0;
	while (i++ < simulation->philosophers_count)
		sem_wait(simulation->philosopher_process_ready);
	i = 0;
	while (i++ < simulation->philosophers_count)
		sem_post(simulation->ready);
}

void	wait_simulation_ends(t_simulation *simulation)
{
	sem_wait(simulation->has_ended);
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
