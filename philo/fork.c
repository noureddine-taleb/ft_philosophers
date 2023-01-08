/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 17:16:55 by ntaleb            #+#    #+#             */
/*   Updated: 2023/01/08 17:00:45 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef BONUS
# include "../philo_bonus/philo_bonus.h"
#else
# include "philo.h"
#endif

int	get_forks(t_philo *philo)
{
	enum e_fork	first_fork;

	first_fork = philo->first_fork;
	pthread_mutex_lock(&philo->forks[first_fork]->lock);
	philo_log_take_fork(philo);
	if (philo->state->number_of_philosophers == 1)
		return (msleep(philo, -1), -1);
	pthread_mutex_lock(&philo->forks[!first_fork]->lock);
	philo_log_take_fork(philo);
	return (0);
}

void	put_forks(t_philo *philo)
{
	enum e_fork	first_fork;

	first_fork = philo->first_fork;
	pthread_mutex_unlock(&philo->forks[first_fork]->lock);
	pthread_mutex_unlock(&philo->forks[!first_fork]->lock);
}
