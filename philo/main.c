/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharuel <tcharuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 15:55:57 by tcharuel          #+#    #+#             */
/*   Updated: 2024/01/11 12:11:44 by tcharuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_state	state;

	if (argc == 5 || argc == 6)
	{
		if (state_init(argc, argv, &state) == ERROR)
		{
			state_cleanup(state);
			return (0);
		}
		printf("Number of philosophers: %u\n", state.number_of_philosophers);
		printf("Time to die: %u\n", state.time_to_die);
		printf("Time to eat: %u\n", state.time_to_eat);
		printf("Time to sleep: %u\n", state.time_to_sleep);
		if (argc == 6)
			printf("Number of times each philosopher must eat: %u\n",
				state.number_of_times_each_philosopher_must_eat);
		wait_simulation_ends(state);
		state_cleanup(state);
	}
	return (0);
}
