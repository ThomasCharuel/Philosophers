/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharuel <tcharuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 18:45:08 by tcharuel          #+#    #+#             */
/*   Updated: 2024/01/11 10:06:22 by tcharuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	state->forks = (t_fork *)malloc(state->number_of_philosophers
			* sizeof(t_fork));
	if (!state->forks)
		return (ERROR);
	state->philosophers = (t_philosopher *)malloc(state->number_of_philosophers
			* sizeof(t_philosopher));
	if (!state->philosophers)
		return (ERROR);
	return (SUCCESS);
}

void	forks_init(t_state state)
{
	size_t	i;

	i = 0;
	while (i < state.number_of_philosophers)
	{
		state.forks[i].is_available = 1;
		pthread_mutex_init(&(state.forks[i].lock), NULL);
	}
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

	if (state.forks)
	{
		i = 0;
		while (i < state.number_of_philosophers)
			pthread_mutex_destroy(&(state.forks[i].lock));
		free(state.forks);
	}
	if (state.philosophers)
		free(state.philosophers);
}
