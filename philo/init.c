/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 13:18:02 by ntaleb            #+#    #+#             */
/*   Updated: 2023/01/08 17:38:12 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef BONUS
# include "../philo_bonus/philo_bonus.h"
#else
# include "philo.h"
#endif

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

t_philo	*init_philos(t_state *state, t_fork *forks)
{
	int		i;
	t_philo	*philos;

	i = 0;
	philos = malloc(state->number_of_philosophers * sizeof(t_philo));
	state->died = 0;
	pthread_mutex_init(&state->table_lock, NULL);
	while (i < state->number_of_philosophers)
	{
		philos[i].forks[FORK_RIGHT] = &forks[i];
		philos[i].forks[FORK_LEFT] = &forks[
			safe_index(i - 1, state->number_of_philosophers)];
		philos[i].first_fork = i % 2;
		philos[i].id = i + 1;
		philos[i].ms_last_meal = 0;
		philos[i].state = state;
		i++;
	}
	return (philos);
}
