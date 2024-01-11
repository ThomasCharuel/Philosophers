/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharuel <tcharuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 18:45:08 by tcharuel          #+#    #+#             */
/*   Updated: 2024/01/11 20:35:28 by tcharuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	forks_init(t_state *state)
{
	size_t	i;

	state->forks = (t_fork *)malloc(state->number_of_philosophers
			* sizeof(t_fork));
	if (!state->forks)
		return (ERROR);
	i = 0;
	while (i < state->number_of_philosophers)
	{
		if (init_lock(&(state->forks[i].lock)) == ERROR)
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}

int	philosopher_init(t_state *state)
{
	size_t	i;

	state->philosophers = (t_philosopher *)malloc(state->number_of_philosophers
			* sizeof(t_philosopher));
	if (!state->philosophers)
		return (ERROR);
	i = 0;
	while (i < state->number_of_philosophers)
	{
		state->philosophers[i].id = i + 1;
		state->philosophers[i].state = IS_THINKING;
		state->philosophers[i].last_eating_timestamp.tv_sec = 0;
		state->philosophers[i].last_eating_timestamp.tv_usec = 0;
		state->philosophers[i].simulation_state = state;
		pthread_create(&(state->philosophers[i].tid), NULL, philosopher_routine,
			&(state->philosophers[i]));
		i++;
	}
	return (SUCCESS);
}
int	state_init(int argc, char **argv, t_state *state)
{
	state->forks = NULL;
	state->philosophers = NULL;
	state->is_running = 1;
	state->number_of_philosophers = ft_atoui(argv[1]);
	state->time_to_die = ft_atoui(argv[2]);
	state->time_to_eat = ft_atoui(argv[3]);
	state->time_to_sleep = ft_atoui(argv[4]);
	if (argc == 5)
		state->number_of_times_each_philosopher_must_eat = 0;
	else
		state->number_of_times_each_philosopher_must_eat = ft_atoui(argv[5]);
	if (init_lock(&(state->turn_lock)) == ERROR
		|| init_lock(&(state->printf_lock)) == ERROR
		|| forks_init(state) == ERROR || philosopher_init(state) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

void	wait_simulation_ends(t_state state)
{
	size_t	i;

	i = 0;
	while (i < state.number_of_philosophers)
		pthread_join(state.philosophers[i++].tid, NULL);
}

void	state_cleanup(t_state state)
{
	size_t	i;

	if (state.turn_lock.is_initialized)
		pthread_mutex_destroy(&(state.turn_lock.mutex));
	if (state.printf_lock.is_initialized)
		pthread_mutex_destroy(&(state.printf_lock.mutex));
	if (state.forks)
	{
		i = 0;
		while (i < state.number_of_philosophers
			&& state.forks[i].lock.is_initialized)
			pthread_mutex_destroy(&(state.forks[i++].lock.mutex));
		free(state.forks);
	}
	if (state.philosophers)
		free(state.philosophers);
}
