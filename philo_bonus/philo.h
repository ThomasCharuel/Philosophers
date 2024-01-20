/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharuel <tcharuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 15:56:41 by tcharuel          #+#    #+#             */
/*   Updated: 2024/01/20 12:53:30 by tcharuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <semaphore.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

# define SUCCESS 0
# define ERROR -1
# define FALSE 0
# define TRUE 1

typedef unsigned char		t_bool;
typedef long int			t_timestamp;

typedef enum e_philosopher_action
{
	PHILOSOPHER_STARTS_THINKING,
	PHILOSOPHER_TAKES_FORK,
	PHILOSOPHER_STARTS_EATING,
	PHILOSOPHER_STARTS_SLEEPING,
	PHILOSOPHER_DIES,
}							t_philosopher_action;

typedef enum e_philosopher_state
{
	PHILOSOPHER_INITIALIZED,
	PHILOSOPHER_IS_THINKING,
	PHILOSOPHER_HAS_ONE_FORK,
	PHILOSOPHER_IS_EATING,
	PHILOSOPHER_IS_SLEEPING,
	PHILOSOPHER_IS_DEAD
}						t_philosopher_state;

typedef enum e_simulation_state
{
	SIMULATION_INITIALIZING = 1,
	SIMULATION_RUNNING = 2,
	SIMULATION_ENDED = 3
}						t_simulation_state;

typedef struct s_simulation
{
	unsigned int		number_of_philosophers;
	unsigned int		time_to_die;
	unsigned int		time_to_eat;
	unsigned int		time_to_sleep;
	t_bool				has_number_of_times_each_philosopher_must_eat;
	unsigned int		number_of_times_each_philosopher_must_eat;
	sem_t				*forks_pair_count;
	sem_t				*philosopher_process_ready;
	sem_t				*ready;
	sem_t				*philosopher_have_eaten_enough;
	pid_t				*philosophers_pid;
}						t_simulation;

typedef struct s_philosopher
{
	unsigned int		id;
	t_philosopher_state	state;
	t_timestamp			last_eating_time;
	t_timestamp			last_sleeping_time;
	t_simulation		*simulation;
	unsigned int		meal_count;
}						t_philosopher;

unsigned int			ft_atoui(char *s);

int						simulation_init(int argc, char **argv,
							t_simulation *simulation);
void					simulation_cleanup(t_simulation *simulation);

void					philosopher_routine(t_simulation *simulation,
							unsigned int philosopher_id);

t_timestamp				get_current_time(void);

void					log_action(t_timestamp action_time,
							t_philosopher_action action, t_philosopher *philo);

#endif
