/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharuel <tcharuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 20:05:49 by tcharuel          #+#    #+#             */
/*   Updated: 2024/01/23 11:07:34 by tcharuel         ###   ########.fr       */
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
