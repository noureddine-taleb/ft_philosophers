/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 18:12:44 by ntaleb            #+#    #+#             */
/*   Updated: 2023/01/07 11:40:23 by ntaleb           ###   ########.fr       */
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

#ifdef BONUS

void	__philo_think(t_philo *philo, int max)
{
	int	time_to_think;
#ifdef BONUS
	time_to_think = philo->state->time_to_die - philo->state->time_to_eat
		- philo->state->time_to_sleep - 5;
	philo_log_think(philo);
	if (time_to_think > 0)
		msleep(min(time_to_think, max));
#else
	msleep(min(1, max));
#endif
}

#else

// void	__philo_think(t_philo *philo, int max)
// {
// 	int	time_to_think;

// 	time_to_think = philo->state->time_to_die - philo->state->time_to_eat
// 		- philo->state->time_to_sleep - 5;
// 	philo_log_think(philo);
// 	if (time_to_think > 0)
// 		msleep(min(time_to_think, max));
// }

void	__philo_think(t_philo *philo, int max)
{
	philo_log_think(philo);
	(void)max;
	msleep(min(1, max));
}

#endif
