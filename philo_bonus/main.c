/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharuel <tcharuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 15:55:57 by tcharuel          #+#    #+#             */
/*   Updated: 2024/01/22 11:51:29 by tcharuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philosophers_have_eaten_enough_monitoring_routine(void *data)
{
	unsigned int	i;
	t_simulation	*simulation;

	simulation = (t_simulation *)data;
	i = 0;
	while (i++ < simulation->number_of_philosophers)
		sem_wait(simulation->philosopher_have_eaten_enough);
	i = 0;
	while (i < simulation->number_of_philosophers)
		kill(simulation->philosophers_monitoring_data[i++].philosopher_pid,
			SIGKILL);
	return (NULL);
}

void	*philosopher_monitoring_routine(void *data)
{
	unsigned int					i;
	t_monitoring_philosopher_data	*monitoring_data;

	monitoring_data = (t_monitoring_philosopher_data *)data;
	waitpid(monitoring_data->philosopher_pid, NULL, 0);
	i = 0;
	while (i < monitoring_data->simulation->number_of_philosophers)
	{
		if (monitoring_data->simulation->philosophers_monitoring_data[i].philosopher_pid != monitoring_data->philosopher_pid)
			kill(monitoring_data->simulation->philosophers_monitoring_data[i].philosopher_pid,
				SIGKILL);
		i++;
	}
	return (NULL);
}

void	wait_simulation_starts(t_simulation *simulation)
{
	unsigned int	i;

	i = 0;
	while (i < simulation->number_of_philosophers)
	{
		sem_wait(simulation->philosopher_process_ready);
		pthread_create(&(simulation->philosophers_monitoring_data[i].tid), NULL,
			philosopher_monitoring_routine,
			&(simulation->philosophers_monitoring_data[i]));
		i++;
	}
	if (simulation->has_number_of_times_each_philosopher_must_eat)
		pthread_create(&(simulation->philosophers_have_eaten_enough_monitoring_tid),
			NULL, philosophers_have_eaten_enough_monitoring_routine,
			&(simulation));
	i = 0;
	while (i++ < simulation->number_of_philosophers)
		sem_post(simulation->ready);
}

void	wait_simulation_ends(t_simulation *simulation)
{
	unsigned int	i;

	i = 0;
	while (i < simulation->number_of_philosophers)
	{
		waitpid(simulation->philosophers_monitoring_data[i].philosopher_pid,
			NULL, 0);
		pthread_join(simulation->philosophers_monitoring_data[i].tid, NULL);
		i++;
	}
	if (simulation->has_number_of_times_each_philosopher_must_eat)
		pthread_join(simulation->philosophers_have_eaten_enough_monitoring_tid,
			NULL);
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
