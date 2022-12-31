/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 13:18:02 by ntaleb            #+#    #+#             */
/*   Updated: 2022/12/31 18:11:23 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_fork	*init_forks(t_state *state)
{
	int		i;
	t_fork	*forks;

	i = 0;
	forks = malloc(state->number_of_philosophers * sizeof(t_fork));
	while (i < state->number_of_philosophers)
		pthread_mutex_init(&forks[i++].lock, NULL);
	return (forks);
}

void	init_work(t_work work_table[3], int start)
{
	int		i;
	t_work	refwork_table[3];

	refwork_table[0] = philo_eat;
	refwork_table[1] = philo_sleep;
	refwork_table[2] = philo_think;
	i = 0;
	while (i < 3)
	{
		work_table[i] = refwork_table[safe_index(start, 3)];
		i++;
		start++;
	}
}

t_philo	*init_philos(t_state *state, t_fork *forks)
{
	int		i;
	t_philo	*philos;

	i = 0;
	philos = malloc(state->number_of_philosophers * sizeof(t_philo));
	while (i < state->number_of_philosophers)
	{
		if (i == state->number_of_philosophers - 1)
			philos[i].next = &philos[0];
		else
			philos[i].next = &philos[i + 1];
		philos[i].forks[FORK_RIGHT] = &forks[i];
		philos[i].forks[FORK_LEFT] = &forks[
			safe_index(i - 1, state->number_of_philosophers)];
		philos[i].first_fork = i % 2;
		philos[i].id = i + 1;
		philos[i].ms_last_meal = 0;
		init_work(philos[i].work, i % 3);
		philos[i].state = state;
		i++;
	}
	return (philos);
}
