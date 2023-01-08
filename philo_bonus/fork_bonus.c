/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 17:16:55 by ntaleb            #+#    #+#             */
/*   Updated: 2023/01/08 17:09:41 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/**
 * get couple forks ATOMICALLY.
*/
void	get_forks(t_philo *philo)
{
	sem_wait(philo->state->table_lock);
	sem_wait(philo->forks->sem);
	philo_log_take_fork(philo);
	check_death(philo);
	if (philo->state->number_of_philosophers == 1)
		msleep(philo, -1);
	sem_wait(philo->forks->sem);
	philo_log_take_fork(philo);
	sem_post(philo->state->table_lock);
}

/**
 * no need to acquire the lock,
 * since the thread has exclusive access to the forks.
*/
void	put_forks(t_philo *philo)
{
	sem_post(philo->forks->sem);
	sem_post(philo->forks->sem);
}
