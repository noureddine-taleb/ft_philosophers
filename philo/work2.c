/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 18:12:44 by ntaleb            #+#    #+#             */
/*   Updated: 2022/12/31 18:14:27 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	__philo_eat(t_philo *philo)
{
	philo->ms_last_meal = mstime();
	philo_log_eat(philo);
	msleep(philo->state->time_to_eat);
}

void	__philo_sleep(t_philo *philo, int max)
{
	philo_log_sleep(philo);
	msleep(min(philo->state->time_to_sleep, max));
}

/**
 * TODO: time to think need a closer investigation
*/
void	__philo_think(t_philo *philo, int max)
{
	int	time_to_think;

	time_to_think = philo->state->time_to_die - philo->state->time_to_eat
		- philo->state->time_to_sleep;
	philo_log_think(philo);
	if (time_to_think >= 0)
		msleep(min(time_to_think, max));
}
