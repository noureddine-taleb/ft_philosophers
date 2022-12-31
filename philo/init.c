/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 13:18:02 by ntaleb            #+#    #+#             */
/*   Updated: 2022/12/31 17:11:58 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	help()
{
	printf("./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
}

int	parse_args(char **argv, int argc, t_state *state)
{
	int	err;

	if (argc < 4)
		return (help(), -1);
	state->number_of_philosophers = ft_atoi_err(argv[0], (err = 0, &err));
	if (err || state->number_of_philosophers <= 1)
		return (printf("number of philosophers should be bigger than 1\n"), -1);
	state->time_to_die = ft_atoi_err(argv[1], (err = 0, &err));
	if (err || state->time_to_die <= 0)
		return (printf("time to die should be bigger than 0\n"), -1);
	state->time_to_eat = ft_atoi_err(argv[2], (err = 0, &err));
	if (err || state->time_to_eat <= 0)
		return (printf("time to eat should be bigger than 0\n"), -1);
	state->time_to_sleep = ft_atoi_err(argv[3], (err = 0, &err));
	if (err || state->time_to_sleep <= 0)
		return (printf("time to sleep should be bigger than 0\n"), -1);
	if (argc == 5)
	{
		state->number_of_times_each_philosopher_must_eat = ft_atoi_err(argv[4], (err = 0, &err));
		if (err || state->number_of_times_each_philosopher_must_eat <= 0)
			return (printf("number_of_times_each_philosopher_must_eat should be bigger than 0\n"), -1);
	}
	else
		state->number_of_times_each_philosopher_must_eat = -1;
	// TODO: to be removed
	if (state->time_to_die <= state->time_to_eat + state->time_to_sleep)
		printf("warn:  time to die is not bigger enough\n");
	return (0);
}

t_fork *init_forks(t_state *state)
{
	int	i;

	i = 0;
	t_fork *forks = malloc(state->number_of_philosophers * sizeof(t_fork));
	while (i < state->number_of_philosophers)
		pthread_mutex_init(&forks[i++].lock, NULL);
	return (forks);
}

/**
 * this routine initialises philo's work table
 * NOTE: 0 <= start < 3
*/
void	init_work(t_work work_table[3], int start)
{
	int	i;
	t_work	refwork_table[3];

	refwork_table[0] = philo_eat;
	refwork_table[1] = philo_sleep;
	refwork_table[2] = philo_think;
	i = 0;
	while  (i < 3)
	{
		work_table[i] = refwork_table[safe_index(start, 3)];
		i++;
		start++;
	}
}

t_philo *init_philos(t_state *state, t_fork *forks)
{
	int		i;

	i = 0;
	t_philo *philos = malloc(state->number_of_philosophers * sizeof(t_philo));
	while (i < state->number_of_philosophers)
	{
		if (i == state->number_of_philosophers - 1)
			philos[i].next = &philos[0];
		else
			philos[i].next = &philos[i + 1];
		philos[i].forks[FORK_RIGHT] = &forks[i];
		philos[i].forks[FORK_LEFT] = &forks[safe_index(i - 1, state->number_of_philosophers)];
		philos[i].first_fork = i % 2;
		philos[i].id = i + 1;
		philos[i].ms_last_meal = 0;
		init_work(philos[i].work, i % 3);
		philos[i].state = state;
		i++;
	}
	return (philos);
}
