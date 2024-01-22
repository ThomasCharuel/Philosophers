/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharuel <tcharuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 20:05:49 by tcharuel          #+#    #+#             */
/*   Updated: 2024/01/22 20:17:11 by tcharuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_lock	*get_left_fork(t_philosopher *philosopher)
{
	t_lock	*fork;

	fork = &(philosopher->simulation->forks[philosopher->id - 1]);
	return (fork);
}

t_lock	*get_right_fork(t_philosopher *philosopher)
{
	t_lock	*fork;

	fork = &(philosopher->simulation->forks[philosopher->id
			% philosopher->simulation->philosophers_count]);
	return (fork);
}

void	philosopher_releases_forks(t_philosopher *philosopher)
{
	if (philosopher->forks[0])
	{
		unlock(philosopher->forks[0]);
		philosopher->forks[0] = NULL;
	}
	if (philosopher->forks[1])
	{
		unlock(philosopher->forks[1]);
		philosopher->forks[1] = NULL;
	}
}
