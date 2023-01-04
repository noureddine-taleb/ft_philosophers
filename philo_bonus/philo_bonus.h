/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noureddine <noureddine@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 13:04:30 by ntaleb            #+#    #+#             */
/*   Updated: 2023/01/06 21:59:34 by noureddine       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <semaphore.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <signal.h>
# include <unistd.h>
# include <fcntl.h>
# include <pthread.h>

# define SEM_FORKS_NAME "forks_sem"
# define SEM_TABLE_NAME "table_sem"

typedef struct s_forks {
	sem_t	*sem;
}	t_forks;

typedef struct s_state {
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				min_eat;
	sem_t			*table_lock;
}	t_state;

typedef struct s_philo {
	pid_t			pid;
	int				finished;
	int				id;
	unsigned long	ms_last_meal;
	t_state			*state;
	t_forks			*forks;
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

void 			get_forks(t_philo *philo);
void 			put_forks(t_philo *philo);

void			__philo_eat(t_philo *philo, int max);
void			__philo_sleep(t_philo *philo, int max);
void			__philo_think(t_philo *philo, int max);

void			philo_eat(t_philo *philo);
void			philo_sleep(t_philo *philo);
void			philo_think(t_philo *philo);

void			help(char *program);
int				parse_args(char **argv, int argc, t_state *state);
t_forks			*init_forks(t_state *state);
t_philo			*init_philos(t_state *state, t_forks *forks);

int				philosopher(void *arg);
void			philo_create(t_philo *philo, int (*main) (void *), void *arg);
int				philo_join(t_philo *philos, t_state	*state);
void			philo_kill_remaining(t_philo *philos, t_state *state);
int				wait_philos(t_philo *philos, t_state *state);

void			cleanup(t_forks *forks);

#endif // PHILO_BONUS_H
