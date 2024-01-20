/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharuel <tcharuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 16:24:59 by tcharuel          #+#    #+#             */
/*   Updated: 2024/01/18 10:54:58 by tcharuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	log_action(t_timestamp action_time, t_philosopher_action action,
		t_philosopher *philo)
{
	t_timestamp	ms_since_start;

	ms_since_start = action_time - philo->simulation->start_time;
	lock(&philo->simulation->printf_lock);
	if (action == PHILOSOPHER_TAKES_FORK)
		printf("%ld %u has taken a fork\n",
			ms_since_start, philo->id);
	else if (action == PHILOSOPHER_STARTS_EATING)
		printf("%ld %u is eating\n", ms_since_start, philo->id);
	else if (action == PHILOSOPHER_STARTS_SLEEPING)
		printf("%ld %u is sleeping\n", ms_since_start, philo->id);
	else if (action == PHILOSOPHER_STARTS_THINKING)
		printf("%ld %u is thinking\n", ms_since_start, philo->id);
	else if (action == PHILOSOPHER_DIES)
		printf("%ld %u died\n", ms_since_start, philo->id);
	unlock(&philo->simulation->printf_lock);
}