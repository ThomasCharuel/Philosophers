/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharuel <tcharuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 15:56:41 by tcharuel          #+#    #+#             */
/*   Updated: 2024/01/18 11:04:32 by tcharuel         ###   ########.fr       */
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
# define FALSE 0
# define TRUE 1

typedef unsigned char		t_bool;
typedef long int			t_timestamp;
typedef struct s_simulation	t_simulation;

typedef enum e_philosopher_action {
	PHILOSOPHER_STARTS_THINKING,
	PHILOSOPHER_TAKES_FORK,
	PHILOSOPHER_STARTS_EATING,
	PHILOSOPHER_STARTS_SLEEPING,
	PHILOSOPHER_DIES,
} t_philosopher_action;

typedef enum e_philosopher_state {
	PHILOSOPHER_INITIALIZED,
	PHILOSOPHER_IS_THINKING,
	PHILOSOPHER_HAS_ONE_FORK,
	PHILOSOPHER_IS_EATING,
	PHILOSOPHER_IS_SLEEPING,
	PHILOSOPHER_IS_DEAD
} t_philosopher_state;

typedef enum e_simulation_state {
	SIMULATION_INITIALIZING,
	SIMULATION_RUNNING,
	SIMULATION_ENDED
} t_simulation_state;

typedef enum e_fork_side {
	LEFT,
	RIGHT
} t_fork_side;

typedef struct s_lock
{
	pthread_mutex_t			mutex;
	bool					is_initialized;
}							t_lock;

typedef struct s_philosopher
{
	pthread_t				tid;
	unsigned int			id;
	t_philosopher_state		state;
	t_lock					state_lock;
	t_timestamp				last_eating_time;
	t_lock					last_eating_time_lock;
	t_timestamp				last_sleeping_time;
	t_lock					last_sleeping_time_lock;
	t_simulation			*simulation;
	unsigned int			meal_count;
	t_lock					meal_count_lock;
}							t_philosopher;

typedef struct s_fork
{
	t_lock					lock;
	t_bool					is_available;
}							t_fork;

typedef struct s_simulation
{
	t_simulation_state		state;
	t_lock					state_lock;
	unsigned int			number_of_philosophers;
	unsigned int			time_to_die;
	unsigned int			time_to_eat;
	unsigned int			time_to_sleep;
	t_bool					has_number_of_times_each_philosopher_must_eat;
	unsigned int			number_of_times_each_philosopher_must_eat;
	t_timestamp				start_time;
	t_lock					printf_lock;
	t_lock					turn;
	t_fork					*forks;
	t_philosopher			*philosophers;
}							t_simulation;

unsigned int				ft_atoui(char *s);

int							simulation_init(int argc, char **argv,
								t_simulation *simulation);
void						wait_simulation_starts(t_simulation *simulation);
void						wait_simulation_ends(t_simulation *simulation);
void						handle_end_simulation(t_simulation *simulation);
void						simulation_cleanup(t_simulation *simulation);

void						*philosopher_routine(void *data);

int							init_lock(t_lock *lock);
void						lock(t_lock *lock);
void						unlock(t_lock *lock);

t_simulation_state			get_simulation_state(t_simulation *simulation);
void						set_simulation_state(t_simulation *simulation,
								t_simulation_state state);
t_philosopher_state			get_philosopher_state(t_philosopher *philosopher);
void						set_philosopher_state(t_philosopher *philosopher,
								t_philosopher_state state);
t_timestamp					get_philosopher_last_eating_time(t_philosopher *philosopher);
void						set_philosopher_last_eating_time(t_philosopher *philosopher,
								t_timestamp last_eating_time);
t_timestamp					get_philosopher_last_sleeping_time(t_philosopher *philosopher);
void						set_philosopher_last_sleeping_time(t_philosopher *philosopher,
								t_timestamp last_sleeping_time);
unsigned int				get_philosopher_meal_count(t_philosopher *philosopher);
void						incr_philosopher_meal_count(t_philosopher *philosopher);
t_bool						get_fork_availability(t_fork *fork);
void						set_fork_availability(t_fork *fork,
								t_bool is_available);

t_timestamp					get_current_time(void);

void	log_action(t_timestamp action_time, t_philosopher_action action,
		t_philosopher *philo);

#endif
