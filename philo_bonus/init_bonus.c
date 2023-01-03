/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 13:18:02 by ntaleb            #+#    #+#             */
/*   Updated: 2023/01/03 12:46:53 by ntaleb           ###   ########.fr       */
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
		philos[i].state = state;
		philos[i].finished = 0;
		philos[i].forks = forks;
		i++;
	}
	return (philos);
}
