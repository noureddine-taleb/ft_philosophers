/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 13:04:30 by ntaleb            #+#    #+#             */
/*   Updated: 2022/12/30 10:49:33 by ntaleb           ###   ########.fr       */
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

typedef struct philo {
  pthread_t 	thread;
  int			id;
  t_fork 		*forks[2];
  struct philo 	*next;
  enum e_fork	first_fork;
  unsigned long	ms_last_meal;
} t_philo;

typedef struct state {
	int number_of_philosophers;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int number_of_times_each_philosopher_must_eat;
	pthread_mutex_t	display_lock;
} t_state;

void	philo_log(t_state *state, char *event, unsigned long mstimestamp, int philo);
int		ft_atoi_err(const char *str, int *error);

#endif // PHILO_H


