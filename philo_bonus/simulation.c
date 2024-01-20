/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharuel <tcharuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 22:58:15 by tcharuel          #+#    #+#             */
/*   Updated: 2024/01/20 12:53:28 by tcharuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philosopher_forks_init(t_simulation *simulation)
{
	size_t	i;

	simulation->philosophers_pid = (t_philosopher *)malloc(simulation->number_of_philosophers
			* sizeof(t_philosopher));
	if (!simulation->philosophers_pid)
		return (ERROR);
	i = 0;
	while (i < simulation->number_of_philosophers)
	{
		simulation->philosophers_pid[i] = fork();
		if (simulation->philosophers_pid[i] == -1)
			return (ERROR); // Kill all process
		if (simulation->philosophers_pid[i] == 0)
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
	simulation->philosophers_pid = NULL;
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
	simulation->forks_pair_count = sem_open(0, O_CREAT, NULL, simulation->number_of_philosophers / 2);
	if (simulation->forks_pair_count == SEM_FAILED)
		return (ERROR);
	simulation->philosopher_process_ready = sem_open(0, O_CREAT, NULL, 0);
	if (simulation->philosopher_process_ready == SEM_FAILED)
		return (ERROR);
	simulation->ready = sem_open(0, O_CREAT, NULL, 0);
	if (simulation->ready == SEM_FAILED)
		return (ERROR);
	if (simulation->has_number_of_times_each_philosopher_must_eat)
	{
		simulation->philosopher_have_eaten_enough = sem_open(0, O_CREAT, NULL, 0);
		if (simulation->philosopher_have_eaten_enough == SEM_FAILED)
			return (ERROR);
	}
	return (philosopher_forks_init(simulation));
}

void	simulation_cleanup(t_simulation *simulation)
{
	if (simulation->forks_pair_count)
		sem_close(&simulation->forks_pair_count);
	if (simulation->philosopher_process_ready)
		sem_close(&simulation->philosopher_process_ready);
	if (simulation->ready)
		sem_close(&simulation->ready);
	if (simulation->philosopher_have_eaten_enough)
		sem_close(&simulation->philosopher_have_eaten_enough);
}
