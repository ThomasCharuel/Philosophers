/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharuel <tcharuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 15:55:57 by tcharuel          #+#    #+#             */
/*   Updated: 2024/01/10 19:06:52 by tcharuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// typedef struct s_counter
// {
// 	pthread_mutex_t	count_mutex;
// 	unsigned int	count;
// }					t_counter;

// void	*thread_routine(void *data)
// {
// 	pthread_t	tid;
// 	t_counter	*counter;

// 	tid = pthread_self();
// 	counter = (t_counter *)data;
// 	pthread_mutex_lock(&counter->count_mutex);
// 	//
// 	pthread_mutex_unlock(&counter->count_mutex);
// 	return (NULL);
// }

// int	main(void)
// {
// 	pthread_t	tid1;
// 	pthread_t	tid2;
// 	t_counter	counter;

// 	counter.count = 0;
// 	pthread_mutex_init(&counter.count_mutex, NULL);
// 	pthread_create(&tid1, NULL, thread_routine, NULL);
// 	pthread_create(&tid2, NULL, thread_routine, NULL);
// 	// The main thread waits for the new threads to end with pthread_join
// 	pthread_join(tid1, NULL);
// 	pthread_join(tid2, NULL);
// 	pthread_mutex_destroy(&counter.count_mutex);
// 	return (0);
// }

int	main(int argc, char **argv)
{
	t_state	state;

	if (argc == 5 || argc == 6)
	{
		if (state_init(argc, argv, &state) == ERROR)
			return (0);
		printf("Number of philosophers: %u\n", state.number_of_philosophers);
		printf("Time to die: %u\n", state.time_to_die);
		printf("Time to eat: %u\n", state.time_to_eat);
		printf("Time to sleep: %u\n", state.time_to_sleep);
		if (argc == 6)
			printf("Number of times each philosopher must eat: %u\n",
				state.number_of_times_each_philosopher_must_eat);
		state_cleanup(state);
	}
	return (0);
}
