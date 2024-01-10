/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharuel <tcharuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 18:45:08 by tcharuel          #+#    #+#             */
/*   Updated: 2024/01/10 19:09:16 by tcharuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	state_init(int argc, char **argv, t_state *state)
{
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
	return (SUCCESS);
}

void	state_cleanup(t_state state)
{
	if (state.fork_mutexes)
		free(state.fork_mutexes);
}
