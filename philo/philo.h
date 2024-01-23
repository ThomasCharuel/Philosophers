/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharuel <tcharuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 18:10:23 by tcharuel          #+#    #+#             */
/*   Updated: 2024/01/23 11:01:56 by tcharuel         ###   ########.fr       */
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

typedef unsigned char			t_bool;
typedef long int				t_timestamp;
typedef struct s_simulation		t_simulation;
typedef struct s_philosopher	t_philosopher;

typedef struct s_lock
{
	pthread_mutex_t				mutex;
	bool						is_initialized;
}								t_lock;

typedef enum e_philosopher_action
{
	PHILOSOPHER_STARTS_THINKING,
	PHILOSOPHER_TAKES_FORK,
	PHILOSOPHER_STARTS_EATING,
	PHILOSOPHER_STARTS_SLEEPING,
	PHILOSOPHER_DIES,
}								t_philosopher_action;

typedef enum e_philosopher_state
{
	PHILOSOPHER_INITIALIZED,
	PHILOSOPHER_IS_THINKING,
	PHILOSOPHER_HAS_ONE_FORK,
	PHILOSOPHER_IS_EATING,
	PHILOSOPHER_IS_SLEEPING,
	PHILOSOPHER_IS_DEAD
}								t_philosopher_state;

typedef struct s_fork
{
	t_lock						lock;
	t_bool						is_available;
	t_philosopher				*last_philosopher;
}								t_fork;

typedef struct s_philosopher
{
	pthread_t					tid;
	unsigned int				id;
	t_philosopher_state			state;
	t_lock						state_lock;
	t_timestamp					last_eating;
	t_lock						last_eating_lock;
	t_timestamp					last_sleeping;
	t_simulation				*simulation;
	unsigned int				meal_count;
	t_lock						meal_count_lock;
	t_fork						*left_fork;
	t_fork						*right_fork;
}								t_philosopher;

typedef enum e_simulation_state
{
	SIMULATION_INITIALIZING,
	SIMULATION_RUNNING,
	SIMULATION_ENDED
}								t_simulation_state;

typedef struct s_simulation
{
	t_simulation_state			state;
	t_lock						state_lock;
	unsigned int				philosophers_count;
	unsigned int				time_to_die;
	unsigned int				time_to_eat;
	unsigned int				time_to_sleep;
	t_bool						has_number_of_times_each_philosopher_must_eat;
	unsigned int				min_meals;
	t_timestamp					start_time;
	t_fork						*forks;
	t_philosopher				*philosophers;
}								t_simulation;

int								simulation_init(int argc, char **argv,
									t_simulation *simulation);
void							simulation_cleanup(t_simulation *simulation);

void							*philosopher_routine(void *data);

void							philosopher_releases_forks(t_philosopher *philosopher);

t_simulation_state				get_simulation_state(t_simulation *simulation);
t_philosopher_state				get_philosopher_state(t_philosopher *philosopher);
t_timestamp						get_philosopher_last_eating(t_philosopher *philosopher);
unsigned int					get_philosopher_meal_count(t_philosopher *philosopher);

void							set_simulation_state(t_simulation *simulation,
									t_simulation_state state);
void							set_philosopher_state(t_philosopher *philosopher,
									t_philosopher_state state);
void							set_philosopher_last_eating(t_philosopher *philosopher,
									t_timestamp last_eating);
void							incr_philosopher_meal_count(t_philosopher *philosopher);

int								init_lock(t_lock *lock);
void							destroy_lock(t_lock *lock);
void							lock(t_lock *lock);
void							unlock(t_lock *lock);

void							log_action(t_timestamp action_time,
									t_philosopher_action action,
									t_philosopher *philo);
t_timestamp						get_current_time(void);
unsigned int					ft_atoui(char *s);

#endif