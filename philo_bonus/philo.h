/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharuel <tcharuel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 15:56:41 by tcharuel          #+#    #+#             */
/*   Updated: 2024/01/22 16:47:30 by tcharuel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <fcntl.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>

# define SUCCESS 0
# define ERROR -1
# define FALSE 0
# define TRUE 1
# define FORKS_PAIR_COUNT_SEM "/forks_pair_count"
# define PHILOSOPHER_PROCESS_READY_SEM "/philosopher_process_ready"
# define READY_SEM "/ready"
# define IS_RUNNING_SEM "/is_running"
# define HAS_ENDED_SEM "/has_ended"
# define PHILOSOPHER_HAVE_EATEN_ENOUGH_SEM "/philosopher_have_eaten_enough"

typedef unsigned char	t_bool;
typedef long int		t_timestamp;

typedef enum e_philosopher_action
{
	PHILOSOPHER_STARTS_THINKING,
	PHILOSOPHER_TAKES_FORK,
	PHILOSOPHER_STARTS_EATING,
	PHILOSOPHER_STARTS_SLEEPING,
	PHILOSOPHER_DIES,
}						t_philosopher_action;

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
	unsigned int		philosophers_count;
	unsigned int		time_to_die;
	unsigned int		time_to_eat;
	unsigned int		time_to_sleep;
	t_bool				has_number_of_times_each_philosopher_must_eat;
	unsigned int		min_meals;
	sem_t				*forks_pair_count;
	sem_t				*philosopher_process_ready;
	sem_t				*ready;
	sem_t				*is_running;
	sem_t				*has_ended;
	sem_t				*philosopher_have_eaten_enough;
	pid_t				*philosopher_pids;
	pthread_t			enough_meal_monitoring_tid;
}						t_simulation;

typedef struct s_philosopher
{
	unsigned int		id;
	t_philosopher_state	state;
	t_timestamp			start_time;
	t_timestamp			last_eating_time;
	t_timestamp			last_sleeping_time;
	t_simulation		*simulation;
	unsigned int		meal_count;
}						t_philosopher;

int						simulation_init(int argc, char **argv,
							t_simulation *simulation);
void					simulation_cleanup(t_simulation *simulation);

void					philosopher_routine(t_simulation *simulation,
							unsigned int philosopher_id);

int						semaphore_init(sem_t **sem, char *name,
							unsigned int value);
int						semaphores_init(t_simulation *simulation);
void					semaphores_cleanup(t_simulation *simulation);

void					log_action(t_timestamp action_time,
							t_philosopher_action action, t_philosopher *philo);
t_timestamp				get_current_time(void);
unsigned int			ft_atoui(char *s);

#endif
