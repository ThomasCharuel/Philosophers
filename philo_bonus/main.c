/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharuel <tcharuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 15:55:57 by tcharuel          #+#    #+#             */
/*   Updated: 2024/01/20 12:56:30 by tcharuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void wait_simulation_starts(t_simulation *simulation)
{
	unsigned int	i;

	i = 0;
	while (i++ < simulation->number_of_philosophers)
		sem_wait(simulation->philosopher_process_ready);
	i = 0;
	while (i++ < simulation->number_of_philosophers)
		sem_post(simulation->philosopher_process_ready);
}

void	philosopher_process_monitoring_routine()
{
	unsigned int	i;
	t_simulation *simulation;

	waitpid(pid);
	i = 0;
	while (i < simulation->number_of_philosophers)
	{
		if (simulation->philosophers_pid[i] != pid)
			kill(simulation->philosophers_pid[i]);
		i++;
	}
}

void philosophers_have_eaten_enough_monitoring_routine()
{
	unsigned int	i;
	t_simulation *simulation;
	
	i++;
	while (i++ < simulation->number_of_philosophers)
		sem_wait(simulation->philosopher_have_eaten_enough);
	i = 0;
	while (i++ < simulation->number_of_philosophers)
		kill(simulation->philosophers_pid[i]);
}

void wait_and_handles_simulation_ends(t_simulation *simulation)
{
	while ()
		thread_join()
	if (simulation->has_number_of_times_each_philosopher_must_eat)
		thread_join()
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
		wait_and_handles_simulation_ends(&simulation);
		simulation_cleanup(&simulation);
	}
	return (0);
}
