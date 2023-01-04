/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noureddine <noureddine@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 17:16:55 by ntaleb            #+#    #+#             */
/*   Updated: 2023/01/04 18:39:10 by noureddine       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef BONUS
# include "../philo_bonus/philo_bonus.h"
#else
# include "philo.h"
#endif

/**
 * get couple forks atomicaly
 * 
*/

void get_forks(t_philo *philo)
{
	t_state *state;
	int		success;

	state = philo->state;
	success = 0;
	while (1)
	{
		while (philo->forks[0]->locked || philo->forks[1]->locked)
			check_death(philo);
		pthread_mutex_lock(&state->table_lock);
		if (!philo->forks[0]->locked && !philo->forks[1]->locked)
		{
			philo->forks[0]->locked = 1;
			philo->forks[1]->locked = 1;
			success = 1;
		}
		pthread_mutex_unlock(&state->table_lock);
		if (success)
			return ;
	}
}

/**
 * no need to acquire the lock,
 * since the thread has exclusive access to the forks
*/
void put_forks(t_philo *philo)
{
	philo->forks[0]->locked = 0;
	philo->forks[1]->locked = 0;
}
