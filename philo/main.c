/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharuel <tcharuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 15:55:57 by tcharuel          #+#    #+#             */
/*   Updated: 2024/01/11 20:39:05 by tcharuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "time.h"

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
		wait_simulation_ends(state);
		// state_cleanup(state);
		sleep(5);
	}
	return (0);
}
