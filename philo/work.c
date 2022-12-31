/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 13:15:51 by ntaleb            #+#    #+#             */
/*   Updated: 2022/12/31 16:37:21 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void __philo_eat(t_philo *philo)
{
	philo->ms_last_meal = mstime();
	philo_log_eat(philo);
	msleep(philo->state->time_to_eat);
}

void __philo_sleep(t_philo *philo, int max)
{
	philo_log_sleep(philo);
	msleep(min(philo->state->time_to_sleep, max));
}

void __philo_think(t_philo *philo, int max)
{
	int	time_to_think;

	// TODO: this is to be calculated in a better way
	time_to_think = 1;
	// time_to_think = philo->state->time_to_die - philo->state->time_to_eat - philo->state->time_to_sleep;
	philo_log_think(philo);
	if (time_to_think >= 0)
		msleep(min(time_to_think, max));
}

void	philo_eat(t_philo *philo)
{
	t_state			*state;

	state = philo->state;
	check_death(philo, 0, 0);
	get_fork(philo, philo->first_fork);
	check_death(philo, 1, 0);
	get_fork(philo, !philo->first_fork);
	check_death(philo, 1, 1);
	__philo_eat(philo);
	put_fork(philo, !philo->first_fork);
	put_fork(philo, philo->first_fork);
}

void	philo_sleep(t_philo *philo)
{
	t_state *state;
	int		rem;

	state = philo->state;
	rem = check_death(philo, 0);
	__philo_sleep(philo, rem);
}

void	philo_think(t_philo *philo)
{
	t_state *state;
	int		rem;

	state = philo->state;
	rem = check_death(philo, 0);
	__philo_think(philo, rem);
}
