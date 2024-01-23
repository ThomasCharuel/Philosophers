/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharuel <tcharuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 20:05:49 by tcharuel          #+#    #+#             */
/*   Updated: 2024/01/23 12:23:39 by tcharuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philosopher_releases_forks(t_philosopher *philosopher)
{
	lock(&philosopher->left_fork->lock);
	if (!philosopher->left_fork->is_available
		&& philosopher->left_fork->last_philosopher == philosopher)
		philosopher->left_fork->is_available = TRUE;
	unlock(&philosopher->left_fork->lock);
	lock(&philosopher->right_fork->lock);
	if (!philosopher->right_fork->is_available
		&& philosopher->right_fork->last_philosopher == philosopher)
		philosopher->right_fork->is_available = TRUE;
	unlock(&philosopher->right_fork->lock);
}

int	get_target_fork(t_philosopher *philosopher)
{
	t_fork	*fork;

	if (philosopher->state == PHILOSOPHER_IS_THINKING)
	{
		if (philosopher->id % 2)
			fork = philosopher->right_fork;
		else
			fork = philosopher->left_fork;
	}
	else if (philosopher->state == PHILOSOPHER_HAS_ONE_FORK)
	{
		if (philosopher->id % 2)
			fork = philosopher->left_fork;
		else
			fork = philosopher->right_fork;
	}
	else
		return (ERROR);
	lock(&fork->lock);
	if (!fork->is_available || fork->last_philosopher == philosopher)
		return (unlock(&fork->lock), ERROR);
	fork->is_available = FALSE;
	fork->last_philosopher = philosopher;
	return (unlock(&fork->lock), SUCCESS);
}
