/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphores.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharuel <tcharuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:44:07 by tcharuel          #+#    #+#             */
/*   Updated: 2024/01/22 16:46:55 by tcharuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	semaphore_init(sem_t **sem, char *name, unsigned int value)
{
	sem_unlink(name);
	*sem = sem_open(name, O_CREAT, S_IRUSR | S_IWUSR, value);
	if (*sem == SEM_FAILED)
		return (ERROR);
	return (SUCCESS);
}

int	semaphores_init(t_simulation *simulation)
{
	return (semaphore_init(&simulation->forks_pair_count, FORKS_PAIR_COUNT_SEM,
			simulation->philosophers_count / 2)
		|| semaphore_init(&simulation->philosopher_process_ready,
			PHILOSOPHER_PROCESS_READY_SEM, 0)
		|| semaphore_init(&simulation->ready, READY_SEM, 0)
		|| semaphore_init(&simulation->is_running, IS_RUNNING_SEM, 1)
		|| semaphore_init(&simulation->has_ended, HAS_ENDED_SEM, 0));
}

void	semaphores_cleanup(t_simulation *simulation)
{
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
