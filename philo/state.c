/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharuel <tcharuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 18:45:08 by tcharuel          #+#    #+#             */
/*   Updated: 2024/01/11 11:32:46 by tcharuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	state_init(int argc, char **argv, t_state *state)
{
	state->forks = NULL;
	state->philosophers = NULL;
	state->turn_lock = NULL;
	state->is_running = 1;
	state->number_of_philosophers = ft_atoui(argv[1]);
	state->time_to_die = ft_atoui(argv[2]);
	state->time_to_eat = ft_atoui(argv[3]);
	state->time_to_sleep = ft_atoui(argv[4]);
	if (argc == 5)
		state->number_of_times_each_philosopher_must_eat = 0;
	else
		state->number_of_times_each_philosopher_must_eat = ft_atoui(argv[5]);
	if (pthread_mutex_init(state->turn_lock, NULL) != 0)
		return (ERROR);
	if (forks_init(state) == ERROR)
		return (ERROR);
	if (philosopher_init(state) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

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
		state->forks[i].is_available = 1;
		state->forks[i].lock = NULL;
		if (pthread_mutex_init(state->forks[i].lock, NULL) != 0)
			return (ERROR);
	}
	return (SUCCESS);
}

int	philosopher_init(t_state *state)
{
	state->philosophers = (t_philosopher *)malloc(state->number_of_philosophers
			* sizeof(t_philosopher));
	if (!state->philosophers)
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

	if (state.turn_lock)
		pthread_mutex_destroy(state.turn_lock);
	if (state.forks)
	{
		i = 0;
		while (state.forks[i].lock)
			pthread_mutex_destroy(state.forks[i].lock);
		free(state.forks);
	}
	if (state.philosophers)
		free(state.philosophers);
}
