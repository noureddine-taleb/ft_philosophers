/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 13:18:02 by ntaleb            #+#    #+#             */
/*   Updated: 2023/01/07 11:55:51 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

sem_t	*_sem_open(char *path, int value)
{
	sem_t	*sem;

	sem = sem_open(path, O_CREAT | O_EXCL, 0664,
			value);
	sem_unlink(path);
	if (sem == SEM_FAILED)
		return (sem);
	return (sem);
}

t_forks	*init_forks(t_state *state)
{
	sem_t	*sem;
	t_forks	*forks;

	sem = _sem_open(SEM_FORKS_NAME, state->number_of_philosophers);
	if (sem == SEM_FAILED)
		return (__perror("semaphore:" SEM_FORKS_NAME " already exists\n"), NULL);
	state->table_lock = _sem_open(SEM_TABLE_NAME, 1);
	if (state->table_lock == SEM_FAILED)
		return (__perror("semaphore:" SEM_TABLE_NAME " already exists\n"), NULL);
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
