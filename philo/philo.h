/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noureddine <noureddine@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 13:04:30 by ntaleb            #+#    #+#             */
/*   Updated: 2023/01/04 16:13:46 by noureddine       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

enum e_fork {
	FORK_LEFT,
	FORK_RIGHT,
};

typedef struct s_fork {
	int	locked;
}	t_fork;

typedef struct s_state {
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				min_eat;
	pthread_mutex_t	table_lock;
}	t_state;

typedef struct s_philo {
	pthread_t		thread;
	int				id;
	t_fork			*forks[2];
	enum e_fork		first_fork;
	unsigned long	ms_last_meal;
	t_state			*state;
	// TODO: remove this
	unsigned long __last_activity;
}	t_philo;

void			philo_log(t_philo *philo, char *event);
void			philo_log_sleep(t_philo *philo);
void			philo_log_think(t_philo *philo);
void			philo_log_eat(t_philo *philo);
void			philo_log_take_fork(t_philo *philo);
void			philo_log_death(t_philo *philo);

int				ft_atoi_err(const char *str, int *error);

unsigned long	mstime(void);
int				safe_index(int i, int len);
int				remaining(t_philo *philo);
void			msleep(int msec);
int				check_death(t_philo *philo);
int				min(int a, int b);
void			__perror(char *err);
int				parse_int(char *str, int *i, int min);

void			get_forks(t_philo *philo);
void			put_forks(t_philo *philo);
void			*philosopher(void *arg);

void			__philo_eat(t_philo *philo, int max);
void			__philo_sleep(t_philo *philo, int max);
void			__philo_think(t_philo *philo, int max);

void			philo_eat(t_philo *philo);
void			philo_sleep(t_philo *philo);
void			philo_think(t_philo *philo);

void			help(char *program);
int				parse_args(char **argv, int argc, t_state *state);
t_fork			*init_forks(t_state *state);
t_philo			*init_philos(t_state *state, t_fork *forks);

#endif // PHILO_H
