/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 10:35:16 by ntaleb            #+#    #+#             */
/*   Updated: 2022/12/31 12:32:56 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long mstime()
{
	struct timeval tv;
	
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int safe_index(int i, int len)
{
	if (i >= 0 && i < len)
		return (i);
	if (i >= len)
		return (i % len);
	i *= -1;
	i %= (len + 1);
	if (i == 0)
		i = 1;
	return (len - i);
}

int remaining(t_philo *philo)
{
	unsigned long curtime;

	curtime = mstime();
	return (philo->state->time_to_die - (curtime - philo->ms_last_meal));
}

void msleep(int msec)
{
	usleep(msec * 1000);
}

int	min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

void	get_fork(t_philo *philo, int i)
{
	pthread_mutex_lock(&philo->forks[i]->lock);
	philo_log_take_fork(philo);
}

void	put_fork(t_philo *philo, int i)
{
	pthread_mutex_unlock(&philo->forks[i]->lock);
}

int	check_death(t_philo *philo, int lock_held)
{
	long	rem;

	rem = remaining(philo);
	if (rem <= 0)
	{
		philo_log_death(philo);
		if (lock_held)
		{
			put_fork(philo, philo->first_fork);
			put_fork(philo, !philo->first_fork);
		}
		exit(1);
	}
	return (rem);
}
