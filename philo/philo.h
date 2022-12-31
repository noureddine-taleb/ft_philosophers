/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 13:04:30 by ntaleb            #+#    #+#             */
/*   Updated: 2022/12/31 16:36:47 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

enum e_fork {
	FORK_LEFT,
	FORK_RIGHT,
};

typedef struct fork {
  pthread_mutex_t lock;
} t_fork;

typedef struct state {
	int number_of_philosophers;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int number_of_times_each_philosopher_must_eat;
	pthread_mutex_t	display_lock;
} t_state;

struct philo;
typedef struct philo t_philo;
typedef void (*t_work)(t_philo *);

struct philo {
  pthread_t		thread;
  int			id;
  t_fork		*forks[2];
  struct philo	*next;
  enum e_fork	first_fork;
  unsigned long	ms_last_meal;
  t_work		work[3];
  t_state		*state;
};

void philo_log_sleep(t_philo *philo);
void philo_log_think(t_philo *philo);
void philo_log_eat(t_philo *philo);
void philo_log_take_fork(t_philo *philo);
void philo_log_death(t_philo *philo);

int		ft_atoi_err(const char *str, int *error);

unsigned long mstime();
int safe_index(int i, int len);
int remaining(t_philo *philo);
void msleep(int msec);
int	check_death(t_philo *philo, int first_lock_held, int second_lock_held);
int	min(int a, int b);

void	get_fork(t_philo *philo, int i);
void	put_fork(t_philo *philo, int i);

void	philo_eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	philo_think(t_philo *philo);

void	help();
int		parse_args(char **argv, int argc, t_state *state);
t_fork	*init_forks(t_state *state);
t_philo *init_philos(t_state *state, t_fork *forks);

#endif // PHILO_H


