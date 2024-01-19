/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharuel <tcharuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 18:45:08 by tcharuel          #+#    #+#             */
/*   Updated: 2024/01/19 22:43:01 by tcharuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	forks_init(t_simulation *simulation)
{
	size_t	i;

	simulation->forks = (t_fork *)malloc(simulation->number_of_philosophers
			* sizeof(t_fork));
	if (!simulation->forks)
		return (ERROR);
	i = 0;
	while (i < simulation->number_of_philosophers)
	{
		simulation->forks[i].is_available = TRUE;
		if (init_lock(&(simulation->forks[i].lock)) == ERROR)
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}

int	philosopher_init(t_simulation *simulation)
{
	size_t	i;

	simulation->philosophers = (t_philosopher *)malloc(simulation->number_of_philosophers
			* sizeof(t_philosopher));
	if (!simulation->philosophers)
		return (ERROR);
	i = 0;
	while (i < simulation->number_of_philosophers)
	{
		simulation->philosophers[i].id = i + 1;
		simulation->philosophers[i].state = PHILOSOPHER_INITIALIZED;
		simulation->philosophers[i].meal_count = 0;
		simulation->philosophers[i].simulation = simulation;
		init_lock(&(simulation->philosophers[i].state_lock)); // TO protect
		init_lock(&(simulation->philosophers[i].last_eating_time_lock));
		init_lock(&(simulation->philosophers[i].last_sleeping_time_lock));
		init_lock(&(simulation->philosophers[i].meal_count_lock));
		pthread_create(&(simulation->philosophers[i].tid), NULL,
			philosopher_routine, &(simulation->philosophers[i]));
		i++;
	}
	return (SUCCESS);
}
int	simulation_init(int argc, char **argv, t_simulation *simulation)
{
	simulation->state = SIMULATION_INITIALIZING;
	simulation->forks = NULL;
	simulation->philosophers = NULL;
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
	if (init_lock(&(simulation->state_lock)) == ERROR
		|| init_lock(&(simulation->printf_lock)) == ERROR
		|| forks_init(simulation) == ERROR
		|| philosopher_init(simulation) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

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
	{
		pthread_join(simulation->philosophers[i].tid, NULL);
		i++;
	}
}

void	wait_simulation_ends(t_simulation *simulation)
{
	t_bool		has_enough_meal;
	size_t		i;
	t_timestamp	current_time;

	while (1)
	{
		i = 0;
		current_time = get_current_time();
		has_enough_meal = simulation->has_number_of_times_each_philosopher_must_eat;
		while (i < simulation->number_of_philosophers)
		{
			has_enough_meal &= (get_philosopher_meal_count(&simulation->philosophers[i]) >= simulation->number_of_times_each_philosopher_must_eat);
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
		if (has_enough_meal)
			return ;
		usleep(10);
	}
}

void	simulation_cleanup(t_simulation *simulation)
{
	size_t	i;

	if (simulation->state_lock.is_initialized)
		pthread_mutex_destroy(&(simulation->state_lock.mutex));
	if (simulation->printf_lock.is_initialized)
		pthread_mutex_destroy(&(simulation->printf_lock.mutex));
	if (simulation->forks)
	{
		i = 0;
		while (i < simulation->number_of_philosophers
			&& simulation->forks[i].lock.is_initialized)
			pthread_mutex_destroy(&(simulation->forks[i++].lock.mutex));
		free(simulation->forks);
	}
	if (simulation->philosophers)
	{
		i = 0;
		while (i < simulation->number_of_philosophers
			&& simulation->philosophers[i].state_lock.is_initialized)
		{
			pthread_mutex_destroy(&(simulation->philosophers[i].state_lock.mutex));
			pthread_mutex_destroy(&(simulation->philosophers[i].last_eating_time_lock.mutex));
			pthread_mutex_destroy(&(simulation->philosophers[i].last_sleeping_time_lock.mutex));
			pthread_mutex_destroy(&(simulation->philosophers[i].meal_count_lock.mutex));
			i++;
		}
		free(simulation->philosophers);
	}
}
