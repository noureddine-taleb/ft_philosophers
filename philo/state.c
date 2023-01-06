/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noureddine <noureddine@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 17:16:55 by ntaleb            #+#    #+#             */
/*   Updated: 2023/01/06 22:14:25 by noureddine       ###   ########.fr       */
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

void	get_forks(t_philo *philo)
{
	t_state	*state;
	int		success;

	state = philo->state;
	success = 0;
	while (1)
	{
		while (philo->forks[FORK_LEFT]->locked
			|| philo->forks[FORK_RIGHT]->locked)
		{
			msleep(1);
			check_death(philo);
		}
		pthread_mutex_lock(&state->table_lock);
		if (!philo->forks[FORK_LEFT]->locked
			&& !philo->forks[FORK_RIGHT]->locked)
		{
			if (!philo->forks[FORK_LEFT]->locked)
			{
				philo->forks[FORK_LEFT]->locked = 1;
				philo_log_take_fork(philo);
				success++;
			}
			if (!philo->forks[FORK_RIGHT]->locked)
			{
				philo->forks[FORK_RIGHT]->locked = 1;
				philo_log_take_fork(philo);
				success++;
			}
		}
		pthread_mutex_unlock(&state->table_lock);
		if (success == 2)
			return ;
	}
}

/**
 * no need to acquire the lock,
 * since the thread has exclusive access to the forks
*/
void	put_forks(t_philo *philo)
{
	philo->forks[0]->locked = 0;
	philo->forks[1]->locked = 0;
}
