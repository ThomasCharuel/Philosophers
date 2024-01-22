/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharuel <tcharuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 18:11:27 by tcharuel          #+#    #+#             */
/*   Updated: 2024/01/22 20:14:48 by tcharuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	forks_init(t_simulation *simulation)
{
	size_t	i;

	simulation->forks = (t_lock *)malloc(simulation->philosophers_count
			* sizeof(t_lock));
	if (!simulation->forks)
		return (ERROR);
	i = 0;
	while (i < simulation->philosophers_count)
	{
		if (init_lock(&simulation->forks[i]) == ERROR)
		{
			while (--i >= 0)
				destroy_lock(&simulation->forks[i]);
			free(simulation->forks);
			simulation->forks = NULL;
			return (ERROR);
		}
		i++;
	}
	return (SUCCESS);
}

int	philosopher_init(t_simulation *simulation)
{
	size_t	i;

	simulation->philosophers = malloc(simulation->philosophers_count
			* sizeof(t_philosopher));
	if (!simulation->philosophers)
		return (ERROR);
	i = 0;
	while (i < simulation->philosophers_count)
	{
		simulation->philosophers[i].id = i + 1;
		simulation->philosophers[i].state = PHILOSOPHER_INITIALIZED;
		simulation->philosophers[i].meal_count = 0;
		simulation->philosophers[i].simulation = simulation;
		simulation->philosophers[i].forks[0] = NULL;
		simulation->philosophers[i].forks[1] = NULL;
		init_lock(&(simulation->philosophers[i].state_lock));
		init_lock(&(simulation->philosophers[i].last_eating_lock));
		init_lock(&(simulation->philosophers[i].meal_count_lock));
		if (!simulation->philosophers[i].state_lock.is_initialized
			|| !simulation->philosophers[i].last_eating_lock.is_initialized
			|| !simulation->philosophers[i].meal_count_lock.is_initialized
			|| pthread_create(&(simulation->philosophers[i].tid), NULL,
				philosopher_routine, &(simulation->philosophers[i])))
		{
			set_simulation_state(simulation, SIMULATION_ENDED);
			while (--i >= 0)
			{
				destroy_lock(&simulation->philosophers[i].state_lock);
				destroy_lock(&(simulation->philosophers[i].last_eating_lock));
				destroy_lock(&(simulation->philosophers[i].meal_count_lock));
				pthread_join(simulation->philosophers[i].tid, NULL);
			}
			free(simulation->philosophers);
			simulation->philosophers = NULL;
			return (ERROR);
		}
		i++;
	}
	return (SUCCESS);
}

int	simulation_init(int argc, char **argv, t_simulation *simulation)
{
	simulation->state = SIMULATION_INITIALIZING;
	simulation->forks = NULL;
	simulation->philosophers = NULL;
	simulation->philosophers_count = ft_atoui(argv[1]);
	simulation->time_to_die = ft_atoui(argv[2]);
	simulation->time_to_eat = ft_atoui(argv[3]);
	simulation->time_to_sleep = ft_atoui(argv[4]);
	if (argc == 5)
		simulation->has_number_of_times_each_philosopher_must_eat = FALSE;
	else
	{
		simulation->has_number_of_times_each_philosopher_must_eat = TRUE;
		simulation->min_meals = ft_atoui(argv[5]);
	}
	return (init_lock(&(simulation->state_lock)) || forks_init(simulation)
		|| philosopher_init(simulation));
}

void	simulation_cleanup(t_simulation *simulation)
{
	size_t	i;

	set_simulation_state(simulation, SIMULATION_ENDED);
	if (simulation->philosophers)
	{
		i = 0;
		while (i < simulation->philosophers_count)
		{
			pthread_join(simulation->philosophers[i].tid, NULL);
			destroy_lock(&simulation->philosophers[i].state_lock);
			destroy_lock(&simulation->philosophers[i].last_eating_lock);
			destroy_lock(&simulation->philosophers[i].meal_count_lock);
			i++;
		}
		free(simulation->philosophers);
	}
	destroy_lock(&simulation->state_lock);
	if (simulation->forks)
	{
		i = 0;
		while (i < simulation->philosophers_count)
			destroy_lock(&simulation->forks[i++]);
		free(simulation->forks);
	}
}
