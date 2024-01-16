/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharuel <tcharuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 16:24:59 by tcharuel          #+#    #+#             */
/*   Updated: 2024/01/16 22:18:38 by tcharuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void log_action(int philo_action, t_philosopher *philo)
{
	struct timeval current_time;
	long int ms_since_start;
	
	gettimeofday(&current_time, NULL);
	ms_since_start = get_timestamp_ms_diff(current_time, philo->simulation->start_time);
	pthread_mutex_lock(&(philo->simulation->printf_lock.mutex));
	if (philo_action == PHILOSOPHER_TAKES_FORK)
		printf("%ld %u has taken a fork\n", ms_since_start, philo->id);
	else if (philo_action == PHILOSOPHER_STARTS_EATING)
		printf("%ld %u is eating\n", ms_since_start, philo->id);
	else if (philo_action == PHILOSOPHER_STARTS_SLEEPING)
		printf("%ld %u is sleeping\n", ms_since_start, philo->id);
	else if (philo_action == PHILOSOPHER_STARTS_THINKING)
		printf("%ld %u is thinking\n", ms_since_start, philo->id);
	else if (philo_action == PHILOSOPHER_DIES)
		printf("%ld %u died\n", ms_since_start, philo->id);
	pthread_mutex_unlock(&(philo->simulation->printf_lock.mutex));
}
