/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharuel <tcharuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 18:11:27 by tcharuel          #+#    #+#             */
/*   Updated: 2024/01/23 12:25:46 by tcharuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	forks_init(t_simulation *simulation)
{
	size_t	i;

	simulation->forks = (t_fork *)malloc(simulation->philosophers_count
			* sizeof(t_fork));
	if (!simulation->forks)
		return (ERROR);
	i = 0;
	while (i < simulation->philosophers_count)
	{
		simulation->forks[i].is_available = TRUE;
		simulation->forks[i].last_philosopher = NULL;
		if (init_lock(&simulation->forks[i].lock) == ERROR)
		{
			while (i-- > 0)
				destroy_lock(&simulation->forks[i].lock);
			free(simulation->forks);
			simulation->forks = NULL;
			return (ERROR);
		}
		i++;
	}
	return (SUCCESS);
}

int	philosopher_init(t_simulation *simulation, size_t i)
{
	simulation->philosophers[i].id = i + 1;
	simulation->philosophers[i].state = PHILOSOPHER_INITIALIZED;
	simulation->philosophers[i].meal_count = 0;
	simulation->philosophers[i].simulation = simulation;
	simulation->philosophers[i].left_fork = &simulation->forks[i];
	simulation->philosophers[i].right_fork = &simulation->forks[(i + 1)
		% simulation->philosophers_count];
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
		return (ERROR);
	}
	return (SUCCESS);
}

int	philosophers_init(t_simulation *simulation)
{
	size_t	i;

	simulation->philosophers = malloc(simulation->philosophers_count
			* sizeof(t_philosopher));
	if (!simulation->philosophers)
		return (ERROR);
	i = 0;
	while (i < simulation->philosophers_count)
	{
		if (philosopher_init(simulation, i) == ERROR)
		{
			while (i-- > 0)
			{
				pthread_join(simulation->philosophers[i].tid, NULL);
				destroy_lock(&simulation->philosophers[i].state_lock);
				destroy_lock(&(simulation->philosophers[i].last_eating_lock));
				destroy_lock(&(simulation->philosophers[i].meal_count_lock));
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
	if (!simulation->philosophers_count || !simulation->time_to_die
		|| !simulation->time_to_eat || !simulation->time_to_sleep)
		return (ERROR);
	if (argc == 5)
		simulation->min_meals = 0;
	else
	{
		simulation->min_meals = ft_atoui(argv[5]);
		if (!simulation->min_meals)
			return (ERROR);
	}
	return (init_lock(&(simulation->state_lock)) || forks_init(simulation)
		|| philosophers_init(simulation));
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
			destroy_lock(&simulation->forks[i++].lock);
		free(simulation->forks);
	}
}
