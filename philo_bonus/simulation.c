/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharuel <tcharuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 22:58:15 by tcharuel          #+#    #+#             */
/*   Updated: 2024/01/21 14:14:53 by tcharuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philosophers_init(t_simulation *simulation)
{
	size_t	i;

	simulation->philosophers_monitoring_data = (t_monitoring_philosopher_data *)malloc(simulation->number_of_philosophers
			* sizeof(t_philosopher));
	if (!simulation->philosophers_monitoring_data)
		return (ERROR);
	i = 0;
	while (i < simulation->number_of_philosophers)
	{
		simulation->philosophers_monitoring_data[i].simulation = simulation;
		simulation->philosophers_monitoring_data[i].philosopher_pid = fork();
		if (simulation->philosophers_monitoring_data[i].philosopher_pid == -1)
			return (ERROR); // Kill all process
		if (simulation->philosophers_monitoring_data[i].philosopher_pid == 0)
			philosopher_routine(simulation, i + 1);
		i++;
	}
	return (SUCCESS);
}

int	simulation_init(int argc, char **argv, t_simulation *simulation)
{
	simulation->forks_pair_count = NULL;
	simulation->philosopher_process_ready = NULL;
	simulation->ready = NULL;
	simulation->philosopher_have_eaten_enough = NULL;
	simulation->philosophers_monitoring_data = NULL;
	simulation->number_of_philosophers = ft_atoui(argv[1]);
	simulation->time_to_die = ft_atoui(argv[2]);
	simulation->time_to_eat = ft_atoui(argv[3]);
	simulation->time_to_sleep = ft_atoui(argv[4]);
	if (argc == 5)
		simulation->has_number_of_times_each_philosopher_must_eat = FALSE;
	else
	{
		simulation->has_number_of_times_each_philosopher_must_eat = TRUE;
		simulation->number_of_times_each_philosopher_must_eat = ft_atoui(argv[5]);
	}
	simulation->forks_pair_count = sem_open("/forks_pair_count", O_CREAT, NULL,
			simulation->number_of_philosophers / 2);
	if (simulation->forks_pair_count == SEM_FAILED)
		return (ERROR);
	simulation->philosopher_process_ready = sem_open("/philosopher_process_ready",
			O_CREAT, NULL, 0);
	if (simulation->philosopher_process_ready == SEM_FAILED)
		return (ERROR);
	simulation->ready = sem_open("/ready", O_CREAT, NULL, 0);
	if (simulation->ready == SEM_FAILED)
		return (ERROR);
	if (simulation->has_number_of_times_each_philosopher_must_eat)
	{
		simulation->philosopher_have_eaten_enough = sem_open("/philosopher_have_eaten_enough",
				O_CREAT, NULL, 0);
		if (simulation->philosopher_have_eaten_enough == SEM_FAILED)
			return (ERROR);
	}
	return (philosophers_init(simulation));
}

void	simulation_cleanup(t_simulation *simulation)
{
	if (simulation->forks_pair_count)
		sem_close(simulation->forks_pair_count);
	if (simulation->philosopher_process_ready)
		sem_close(simulation->philosopher_process_ready);
	if (simulation->ready)
		sem_close(simulation->ready);
	if (simulation->philosopher_have_eaten_enough)
		sem_close(simulation->philosopher_have_eaten_enough);
	if (simulation->philosophers_monitoring_data)
		free(simulation->philosophers_monitoring_data);
}
