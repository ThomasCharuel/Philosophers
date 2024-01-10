/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharuel <tcharuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 15:56:41 by tcharuel          #+#    #+#             */
/*   Updated: 2024/01/10 22:53:09 by tcharuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define SUCCESS 0
# define ERROR -1
# define IS_EATING 1
# define IS_SLEEPING 2
# define IS_THINKING 3
# define IS_DEAD 4

typedef int				t_philosopher_state;

typedef struct s_philosopher
{
	pthread_t			tid;
	t_philosopher_state	state;
	struct timeval		last_eating_timestamp;
}						t_philosopher;

typedef struct s_state
{
	unsigned int		number_of_philosophers;
	unsigned int		time_to_die;
	unsigned int		time_to_eat;
	unsigned int		time_to_sleep;
	unsigned int		number_of_times_each_philosopher_must_eat;
	pthread_mutex_t		*fork_mutexes;
	t_philosopher		*philosophers;
}						t_state;

unsigned int			ft_atoui(char *s);

int						state_init(int argc, char **argv, t_state *state);
void					mutex_init(t_state state);
void					state_cleanup(t_state state);

#endif
