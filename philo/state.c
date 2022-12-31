/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 17:16:55 by ntaleb            #+#    #+#             */
/*   Updated: 2022/12/31 17:19:17 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	get_fork(t_philo *philo, int i)
{
	pthread_mutex_lock(&philo->forks[i]->lock);
	philo_log_take_fork(philo);
}

void	put_fork(t_philo *philo, int i)
{
	pthread_mutex_unlock(&philo->forks[i]->lock);
}

int	check_death(t_philo *philo)
{
	long	rem;

	rem = remaining(philo);
	if (rem <= 0)
		exit((philo_log_death(philo), 1));
	return (rem);
}

int	remaining(t_philo *philo)
{
	unsigned long	curtime;

	curtime = mstime();
	return (philo->state->time_to_die - (curtime - philo->ms_last_meal));
}
