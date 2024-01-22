/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharuel <tcharuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 22:58:15 by tcharuel          #+#    #+#             */
/*   Updated: 2024/01/22 15:14:35 by tcharuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philosophers_init(t_simulation *simulation)
{
	size_t	i;

	simulation->philosopher_pids = (pid_t *)malloc(simulation->philosophers_count
			* sizeof(pid_t));
	if (!simulation->philosopher_pids)
		return (ERROR);
	i = 0;
	while (i < simulation->philosophers_count)
	{
		simulation->philosopher_pids[i] = fork();
		if (simulation->philosopher_pids[i] == -1)
			return (ERROR); // Kill all process
		if (simulation->philosopher_pids[i] == 0)
			philosopher_routine(simulation, i + 1);
		i++;
	}
	return (SUCCESS);
}

int	semaphore_init(sem_t **sem, char *name, unsigned int value)
{
	sem_unlink(name);
	*sem = sem_open(name, O_CREAT, S_IRUSR | S_IWUSR, value);
	if (*sem == SEM_FAILED)
		return (ERROR);
	return (SUCCESS);
}

int	simulation_init(int argc, char **argv, t_simulation *simulation)
{
	simulation->forks_pair_count = NULL;
	simulation->philosopher_process_ready = NULL;
	simulation->ready = NULL;
	simulation->is_running = NULL;
	simulation->has_ended = NULL;
	simulation->philosopher_have_eaten_enough = NULL;
	simulation->philosopher_pids = NULL;
	simulation->philosophers_count = ft_atoui(argv[1]);
	simulation->time_to_die = ft_atoui(argv[2]);
	simulation->time_to_eat = ft_atoui(argv[3]);
	simulation->time_to_sleep = ft_atoui(argv[4]);
	simulation->is_running = NULL;
	if (argc == 5)
		simulation->has_number_of_times_each_philosopher_must_eat = FALSE;
	else
	{
		simulation->has_number_of_times_each_philosopher_must_eat = TRUE;
		simulation->number_of_times_each_philosopher_must_eat = ft_atoui(argv[5]);
		if (semaphore_init(&simulation->philosopher_have_eaten_enough,
				PHILOSOPHER_HAVE_EATEN_ENOUGH_SEM, 0) == ERROR)
			return (ERROR);
	}
	if (semaphore_init(&simulation->forks_pair_count, FORKS_PAIR_COUNT_SEM,
			simulation->philosophers_count / 2) == ERROR)
		return (ERROR);
	if (semaphore_init(&simulation->philosopher_process_ready,
			PHILOSOPHER_PROCESS_READY_SEM, 0) == ERROR)
		return (ERROR);
	if (semaphore_init(&simulation->ready, READY_SEM, 0) == ERROR)
		return (ERROR);
	if (semaphore_init(&simulation->is_running, IS_RUNNING_SEM, 1) == ERROR)
		return (ERROR);
	if (semaphore_init(&simulation->has_ended, HAS_ENDED_SEM, 0) == ERROR)
		return (ERROR);
	return (philosophers_init(simulation));
}

void	simulation_cleanup(t_simulation *simulation)
{
	size_t	i;

	if (simulation->philosopher_pids)
	{
		i = 0;
		while (i < simulation->philosophers_count)
			kill(simulation->philosopher_pids[i++], SIGKILL);
		free(simulation->philosopher_pids);
	}
	if (simulation->philosopher_have_eaten_enough)
	{
		i = 0;
		while (i < simulation->philosophers_count)
		{
			sem_post(simulation->philosopher_have_eaten_enough);
			i++;
		}
		sem_post(simulation->is_running);
		pthread_join(simulation->philosophers_have_eaten_enough_monitoring_tid,
			NULL);
		sem_close(simulation->philosopher_have_eaten_enough);
	}
	if (simulation->forks_pair_count)
		sem_close(simulation->forks_pair_count);
	if (simulation->philosopher_process_ready)
		sem_close(simulation->philosopher_process_ready);
	if (simulation->ready)
		sem_close(simulation->ready);
	if (simulation->is_running)
		sem_close(simulation->is_running);
	if (simulation->has_ended)
		sem_close(simulation->has_ended);
}
