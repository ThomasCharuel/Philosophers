/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharuel <tcharuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 15:55:57 by tcharuel          #+#    #+#             */
/*   Updated: 2024/01/17 20:18:37 by tcharuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_simulation	simulation;

	if (argc == 5 || argc == 6)
	{
		if (simulation_init(argc, argv, &simulation) == ERROR)
		{
			simulation_cleanup(&simulation);
			return (0);
		}
		wait_simulation_starts(&simulation);
		wait_simulation_ends(&simulation);
		handle_end_simulation(&simulation);
		simulation_cleanup(&simulation);
	}
	return (0);
}
