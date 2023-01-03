/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntaleb <ntaleb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 13:15:51 by ntaleb            #+#    #+#             */
/*   Updated: 2023/01/03 12:37:51 by ntaleb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_eat(t_philo *philo)
{
	t_state			*state;

	state = philo->state;
	check_death(philo);
	get_fork(philo);
	check_death(philo);
	get_fork(philo);
	check_death(philo);
	philo->ms_last_meal = mstime();
	__philo_eat(philo, philo->ms_last_meal);
	put_fork(philo);
	put_fork(philo);
}

void	philo_sleep(t_philo *philo)
{
	t_state	*state;
	int		rem;

	state = philo->state;
	rem = check_death(philo);
	__philo_sleep(philo, rem);
}

void	philo_think(t_philo *philo)
{
	t_state	*state;
	int		rem;

	state = philo->state;
	rem = check_death(philo);
	__philo_think(philo, rem);
}
