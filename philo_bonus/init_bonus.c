/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 13:18:02 by ntaleb            #+#    #+#             */
/*   Updated: 2023/01/02 18:08:35 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_forks	*init_forks(t_state *state)
{
	sem_t	*sem;
	t_forks	*forks;

	sem = sem_open(SEM_NAME, O_CREAT | O_EXCL, 0664,
			state->number_of_philosophers);
	if (sem == SEM_FAILED)
		return (__perror("semaphore: forks_sem already exists\n"), NULL);
	forks = malloc(sizeof (t_forks));
	forks->sem = sem;
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

t_philo	*init_philos(t_state *state, t_forks *forks)
{
	int		i;
	t_philo	*philos;

	i = 0;
	philos = malloc(state->number_of_philosophers * sizeof(t_philo));
	while (i < state->number_of_philosophers)
	{
		philos[i].id = i + 1;
		philos[i].ms_last_meal = 0;
		init_work(philos[i].work, i % 3);
		philos[i].state = state;
		philos[i].finished = 0;
		philos[i].forks = forks;
		i++;
	}
	return (philos);
}
