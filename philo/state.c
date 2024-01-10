/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharuel <tcharuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 18:45:08 by tcharuel          #+#    #+#             */
/*   Updated: 2024/01/10 22:58:16 by tcharuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	state_init(int argc, char **argv, t_state *state)
{
	state->fork_mutexes = NULL;
	state->philosophers = NULL;
	state->number_of_philosophers = ft_atoui(argv[1]);
	state->time_to_die = ft_atoui(argv[2]);
	state->time_to_eat = ft_atoui(argv[3]);
	state->time_to_sleep = ft_atoui(argv[4]);
	if (argc == 5)
		state->number_of_times_each_philosopher_must_eat = 0;
	else
		state->number_of_times_each_philosopher_must_eat = ft_atoui(argv[5]);
	state->fork_mutexes = (pthread_mutex_t *)malloc(state->number_of_philosophers
			* sizeof(pthread_mutex_t));
	if (!state->fork_mutexes)
		return (ERROR);
	state->philosophers = (t_philosopher *)malloc(state->number_of_philosophers
			* sizeof(t_philosopher));
	if (!state->philosophers)
		return (ERROR);
	return (SUCCESS);
}

void	mutex_init(t_state state)
{
	size_t	i;

	i = 0;
	while (i < state.number_of_philosophers)
		pthread_mutex_init(&(state.fork_mutexes[i++]), NULL);
}

void	state_cleanup(t_state state)
{
	size_t	i;

	if (state.fork_mutexes)
	{
		i = 0;
		while (i < state.number_of_philosophers)
			pthread_mutex_destroy(&(state.fork_mutexes[i++]));
		free(state.fork_mutexes);
	}
	if (state.philosophers)
		free(state.philosophers);
}