/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 18:12:44 by ntaleb            #+#    #+#             */
/*   Updated: 2023/01/07 16:57:30 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef BONUS
# include "../philo_bonus/philo_bonus.h"
#else
# include "philo.h"
#endif

void	__philo_eat(t_philo *philo, int max)
{
	philo_log_eat(philo);
	msleep(min(philo->state->time_to_eat, max));
}

void	__philo_sleep(t_philo *philo, int max)
{
	philo_log_sleep(philo);
	msleep(min(philo->state->time_to_sleep, max));
}

void	__philo_think(t_philo *philo, int rem)
{
	int	time_to_think;

	time_to_think = rem / 2;
	philo_log_think(philo);
	if (time_to_think > 9)
		msleep(time_to_think);
}
