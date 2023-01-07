/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 17:16:55 by ntaleb            #+#    #+#             */
/*   Updated: 2023/01/07 11:55:04 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef BONUS
# include "../philo_bonus/philo_bonus.h"
#else
# include "philo.h"
#endif

int	__get_fork(t_philo *philo, enum e_fork fork)
{
	if (!philo->forks[fork]->locked)
	{
		philo->forks[fork]->locked = 1;
		philo_log_take_fork(philo);
		return (1);
	}
	return (0);
}

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
			msleep((check_death(philo), 1));
		pthread_mutex_lock(&state->table_lock);
		if (!philo->forks[FORK_LEFT]->locked
			&& !philo->forks[FORK_RIGHT]->locked)
		{
			if (__get_fork(philo, FORK_LEFT))
				success++;
			if (__get_fork(philo, FORK_RIGHT))
				success++;
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
