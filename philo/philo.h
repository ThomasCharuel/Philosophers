/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharuel <tcharuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 15:56:41 by tcharuel          #+#    #+#             */
/*   Updated: 2024/01/16 22:04:42 by tcharuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define SUCCESS 0
# define ERROR -1
# define PHILOSOPHER_INITIALIZED 1
# define PHILOSOPHER_IS_EATING 2
# define PHILOSOPHER_IS_SLEEPING 3
# define PHILOSOPHER_IS_THINKING 4
# define PHILOSOPHER_IS_DEAD 5
# define PHILOSOPHER_TAKES_FORK 1
# define PHILOSOPHER_STARTS_EATING 2
# define PHILOSOPHER_STARTS_SLEEPING 3
# define PHILOSOPHER_STARTS_THINKING 4
# define PHILOSOPHER_DIES 5
# define SIMULATION_INITIALIZING 1
# define SIMULATION_RUNNING 2
# define SIMULATION_ENDED 3

typedef unsigned int		t_philosopher_state;
typedef unsigned int		t_simulation_state;
typedef struct s_simulation	t_simulation;

typedef struct s_lock
{
	pthread_mutex_t		mutex;
	bool				is_initialized;
}						t_lock;

typedef struct s_philosopher
{
	pthread_t			tid;
	unsigned int		id;
	t_philosopher_state	state;
	t_lock				state_lock;
	struct timeval		last_eating_timestamp;
	t_simulation		*simulation;
}						t_philosopher;

typedef struct s_fork
{
	t_lock				lock;
	bool				is_available;
}						t_fork;

typedef struct s_simulation
{
	t_simulation_state	state;
	t_lock				state_lock;
	unsigned int		number_of_philosophers;
	unsigned int		time_to_die;
	unsigned int		time_to_eat;
	unsigned int		time_to_sleep;
	unsigned int		number_of_times_each_philosopher_must_eat;
	struct timeval		start_time;
	t_lock				printf_lock;
	t_lock				turn;
	t_fork				*forks;
	t_philosopher		*philosophers;
}						t_simulation;

unsigned int			ft_atoui(char *s);

int						simulation_init(int argc, char **argv, t_simulation *simulation);
void					wait_simulation_starts(t_simulation *simulation);
void					wait_simulation_ends(t_simulation *simulation);
void					simulation_cleanup(t_simulation *simulation);

void					*philosopher_routine(void *data);

int						init_lock(t_lock *lock);
t_simulation_state get_simulation_state(t_simulation *simulation);
void set_simulation_state(t_simulation *simulation, t_simulation_state state);
t_philosopher_state get_philosopher_state(t_philosopher *philosopher);
void set_philosopher_state(t_philosopher *philosopher, t_philosopher_state state);

long int	get_timestamp_ms_diff(struct timeval a, struct timeval b);

void					log_action(int philo_action, t_philosopher *philo);

#endif
